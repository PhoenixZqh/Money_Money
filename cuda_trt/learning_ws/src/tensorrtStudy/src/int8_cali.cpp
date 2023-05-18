#include <cuda_runtime.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <memory>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <stdio.h>
#include <tensorrtStudy/NvInfer.h>
#include <tensorrtStudy/NvInferRuntime.h>
#include <tensorrtStudy/NvOnnxParser.h>
#include <tensorrtStudy/logging.h>
#include <vector>

static Logger gLogger;
using namespace std;
using namespace nvinfer1;

const int in_batch = 1;
const int in_channel = 3;
const int in_height = 224;
const int in_width = 224;
const int in_numel = in_batch * in_channel * in_height * in_width;
const int num_class = 1000;

#define checkRuntime(op) __check_cuda_runtime((op), #op, __FILE__, __LINE__)

bool __check_cuda_runtime(cudaError_t code, const char* op, const char* file, int line)
{
    if (code != cudaSuccess) {
        const char* err_name = cudaGetErrorName(code);
        const char* err_message = cudaGetErrorString(code);
        printf("runtime error %s:%d  %s failed. \n  code = %s, message = %s\n", file, line, op, err_name, err_message);
        return false;
    }
    return true;
}

inline const char* severity_string(ILogger::Severity t)
{
    switch (t) {
    case ILogger::Severity::kINTERNAL_ERROR:
        return "internal_error";
    case ILogger::Severity::kERROR:
        return "error";
    case ILogger::Severity::kWARNING:
        return "warning";
    case ILogger::Severity::kINFO:
        return "info";
    case ILogger::Severity::kVERBOSE:
        return "verbose";
    default:
        return "unknow";
    }
}

class TRTLogger : public ILogger {
public:
    virtual void log(Severity severity, AsciiChar const* msg) noexcept override
    {
        if (severity <= Severity::kINFO) {
            // 打印带颜色的字符，格式如下：
            // printf("\033[47;33m打印的文本\033[0m");
            // 其中 \033[ 是起始标记
            //      47    是背景颜色
            //      ;     分隔符
            //      33    文字颜色
            //      m     开始标记结束
            //      \033[0m 是终止标记
            // 其中背景颜色或者文字颜色可不写
            // 部分颜色代码 https://blog.csdn.net/ericbar/article/details/79652086
            if (severity == Severity::kWARNING) {
                printf("\033[33m%s: %s\033[0m\n", severity_string(severity), msg);
            } else if (severity <= Severity::kERROR) {
                printf("\033[31m%s: %s\033[0m\n", severity_string(severity), msg);
            } else {
                printf("%s: %s\n", severity_string(severity), msg);
            }
        }
    }
} logger;

typedef std::function<void(int current, int count, const std::vector<std::string>& files, Dims dims, float* ptensor)> Int8Process; // 实现回调函数

//*** INT8 熵校准器，用来评估量化前后的分布改变
class Int8EntroyCalibrator : public IInt8EntropyCalibrator2 {
private:
    Int8Process preprocess_;
    vector<string> allimgs_;
    size_t batchCudaSize_ = 0;
    int cursor_ = 0;
    size_t bytes_ = 0;
    Dims dims_;
    vector<string> files_;
    float* h_tensor = nullptr;
    float* d_tensor = nullptr;
    vector<uint8_t> entroyCalibratorData_;
    bool fromCalibratorData_ = false;

public:
    Int8EntroyCalibrator(const vector<string>& imagefiles, Dims dims, const Int8Process& preprocess)
        : dims_(dims)
        , allimgs_(imagefiles)
        , preprocess_(preprocess)
        , fromCalibratorData_(false)
    {
        assert(preprocess != nullptr);
        files_.resize(dims.d[0]);
    }

    // 此构造函数，
    Int8EntroyCalibrator(const vector<uint8_t> entroyCalibratorData, Dims dims, const Int8Process preprocess)
        : dims_(dims)
        , entroyCalibratorData_(entroyCalibratorData)
        , preprocess_(preprocess)
        , fromCalibratorData_(true)
    {
        assert(preprocess != nullptr);
        files_.resize(dims.d[0]);
    }

    virtual ~Int8EntroyCalibrator()
    {
        if (h_tensor != nullptr) {
            checkRuntime(cudaFreeHost(h_tensor));
            checkRuntime(cudaFree(d_tensor));

            h_tensor = nullptr;
            d_tensor = nullptr;
        }
    }

    int getBatchSize() const noexcept
    {
        return dims_.d[0];
    }

    bool Next()
    {
        int batch_size = dims_.d[0]; // batch, channel ,width,height
        if (cursor_ + batch_size > allimgs_.size())
            return false;

        for (int i = 0; i < batch_size; ++i) {
            files_[i] = allimgs_[cursor_++];
        }

        if (h_tensor == nullptr) {
            size_t volumn = 1;
            for (int i = 0; i < dims_.nbDims; ++i) { // dims.nbDims指的是有几个维度，这里是4
                volumn *= dims_.d[i];
            }

            bytes_ = volumn * sizeof(float); // 算出总的字节数

            checkRuntime(cudaMallocHost(&h_tensor, bytes_));
            checkRuntime(cudaMalloc(&d_tensor, bytes_));
        }

        preprocess_(cursor_, allimgs_.size(), files_, dims_, h_tensor);
        checkRuntime(cudaMemcpy(d_tensor, h_tensor, bytes_, cudaMemcpyHostToDevice));
        return true;
    }

    bool getBatch(void* bindings[], const char* names[], int nBindings) noexcept
    {
        if (!Next())
            return false;

        bindings[0] = d_tensor;
        return true;
    }

    const vector<uint8_t>& getEntropyCalibratorData()
    {
        return entroyCalibratorData_;
    }

    const void* readCalibrationCache(size_t& length) noexcept
    {
        if (fromCalibratorData_) {
            length = this->entroyCalibratorData_.size();
            return this->entroyCalibratorData_.data();
        }

        return nullptr;
    }

    virtual void writeCalibrationCache(const void* cache, size_t length) noexcept
    {
        entroyCalibratorData_.assign((uint8_t*)cache, (uint8_t*)cache + length);
    }
};

template <typename _T>
static shared_ptr<_T> make_nvshared(_T* ptr)
{
    return shared_ptr<_T>(ptr, [](_T* p) { p->destroy(); });
}

static bool exists(const string& path)
{

#ifdef _WIN32
    return ::PathFileExistsA(path.c_str());
#else
    return access(path.c_str(), R_OK) == 0;
#endif
}

// 构建网络模型
bool BuildModel()
{
    if (exists("int8_cali.engine")) {
        ROS_INFO("engine existed.");
        return true;
    }

    TRTLogger logger;

    auto builder = make_nvshared(createInferBuilder(logger)); // 创建builder的时候需要logger
    auto config = make_nvshared(builder->createBuilderConfig());
    auto network = make_nvshared(builder->createNetworkV2(1)); // 这里打1是什么意思？

    // 将onnx_parser解析的结果填充到network中去
    auto parser = make_nvshared(nvonnxparser::createParser(*network, logger)); // 创建parser需要logger
    if (!parser->parseFromFile("/home/zqh/CODE/Cuda-TensorRT/learning_ws/src/tensorrtStudy/Model/classfier.onnx", 1)) {
        ROS_INFO("failed to parse onnx .");
        return false;
    }

    int maxBatchSize = 10;
    config->setMaxWorkspaceSize(1 << 28);

    // 模型有多个输入则配备多个profile
    auto profile = builder->createOptimizationProfile();
    auto input_tensor = network->getInput(0);
    auto input_dims = input_tensor->getDimensions();

    //***************************** INT8 *******************************************//
    input_dims.d[0] = 1;
    config->setFlag(BuilderFlag::kINT8); // 这句干嘛用的???

    auto preprocess = [](int current, int count, const std::vector<std::string>& files, Dims dims, float* ptensor) {
        std::cout << "count: " << count << "\t"
                  << "current: " << current
                  << std::endl;

        // 标定所采用的数据预处理必须与推理时一样
        int height = dims.d[2];
        int width = dims.d[3];

        float mean[] = { 0.406, 0.456, 0.485 };
        float std[] = { 0.225, 0.224, 0.229 };

        for (int i = 0; i < files.size(); ++i) {
            auto image = cv::imread(files[i]);
            cv::resize(image, image, cv::Size(width, height));

            int image_area = width * height;
            unsigned char* pimage = image.data;
            float* phost_b = ptensor + image_area * 0;
            float* phost_g = ptensor + image_area * 1;
            float* phost_r = ptensor + image_area * 2;
            for (int i = 0; i < image_area; ++i, pimage += 3) {
                // 注意这里的顺序rgb调换了
                *phost_r++ = (pimage[0] / 255.0f - mean[0]) / std[0];
                *phost_g++ = (pimage[1] / 255.0f - mean[1]) / std[1];
                *phost_b++ = (pimage[2] / 255.0f - mean[2]) / std[2];
            }
            ptensor += image_area * 3;
        }
    };

    // 配置INT8标定读取工具
    shared_ptr<Int8EntroyCalibrator> calib(new Int8EntroyCalibrator({ "/home/zqh/CODE/Cuda-TensorRT/learning_ws/src/tensorrtStudy/workspace/kej.jpg" }, input_dims, preprocess));
    config->setInt8Calibrator(calib.get()); // calib.get???  实现校准器后， 用此方法配置构建器

    input_dims.d[0] = 1;
    profile->setDimensions(input_tensor->getName(), OptProfileSelector::kMIN, input_dims);
    profile->setDimensions(input_tensor->getName(), OptProfileSelector::kOPT, input_dims);

    input_dims.d[0] = maxBatchSize;
    profile->setDimensions(input_tensor->getName(), OptProfileSelector::kMAX, input_dims);

    config->addOptimizationProfile(profile); // 将配置添加到config中

    auto engine = make_nvshared(builder->buildEngineWithConfig(*network, *config)); // 构建INT8引擎
    assert(engine != nullptr);

    // 模型序列化保存到文件中
    auto model_data = make_nvshared(engine->serialize());
    FILE* f = fopen("/home/zqh/CODE/Cuda-TensorRT/learning_ws/src/tensorrtStudy/Model/int8_cali.engine", "wb");
    fwrite(model_data->data(), 1, model_data->size(), f);
    fclose(f);

    f = fopen("/home/zqh/CODE/Cuda-TensorRT/learning_ws/src/tensorrtStudy/workspace/calib.txt", "wb");
    auto calib_data = calib->getEntropyCalibratorData();
    fwrite(calib_data.data(), 1, calib_data.size(), f);
    fclose(f);

    ROS_INFO("DONE .");
    return true;
}

vector<unsigned char> LoadFile(const string& file)
{
    ifstream in(file, ios::in | ios::binary);
    if (!in.is_open())
        return {};

    in.seekg(0, ios::end);
    size_t length = in.tellg();

    std::vector<uint8_t> data;
    if (length > 0) {
        in.seekg(0, ios::beg);
        data.resize(length);

        in.read((char*)&data[0], length);
    }
    in.close();
    return data;
}

vector<string> LoadLabels(const char* file)
{
    vector<string> lines;

    ifstream in(file, ios::in | ios::binary);
    if (!in.is_open()) {
        printf("open %d failed.\n", file);
        return lines;
    }

    string line;
    while (getline(in, line)) {
        lines.push_back(line);
    }
    in.close();
    return lines;
}

void Inference()
{
    auto engine_data = LoadFile("/home/zqh/CODE/Cuda-TensorRT/learning_ws/src/tensorrtStudy/Model/int8_cali.engine");
    auto runtime = make_nvshared(createInferRuntime(logger));
    auto engine = make_nvshared(runtime->deserializeCudaEngine(engine_data.data(), engine_data.size())); // 发序列化的到engine
    assert(engine != nullptr);

    // 创建流
    cudaStream_t stream = nullptr;
    checkRuntime(cudaStreamCreate(&stream));
    auto execution_context = make_nvshared(engine->createExecutionContext()); // engine创建上下文，上下文执行推理

    float* h_in = nullptr;
    float* d_in = nullptr;

    checkRuntime(cudaMallocHost(&h_in, in_numel * sizeof(float)));
    checkRuntime(cudaMalloc(&d_in, in_numel * sizeof(float)));

    // 预处理过程，将图像变成float类型表示
    auto image = cv::imread("/home/zqh/CODE/Cuda-TensorRT/learning_ws/src/tensorrtStudy/workspace/ng.jpg");
    float mean[] = { 0.406, 0.456, 0.485 };
    float std[] = { 0.225, 0.224, 0.229 };

    cv::resize(image, image, cv::Size(in_width, in_height));
    int image_area = image.cols * image.rows;
    unsigned char* pimage = image.data;
    float* phost_b = h_in + image_area * 0;
    float* phost_g = h_in + image_area * 1;
    float* phost_r = h_in + image_area * 2;
    for (int i = 0; i < image_area; ++i, pimage += 3) {
        // 注意这里的顺序rgb调换了
        *phost_r++ = (pimage[0] / 255.0f - mean[0]) / std[0];
        *phost_g++ = (pimage[1] / 255.0f - mean[1]) / std[1];
        *phost_b++ = (pimage[2] / 255.0f - mean[2]) / std[2];
    }

    checkRuntime(cudaMemcpyAsync(d_in, h_in, in_numel * sizeof(float), cudaMemcpyHostToDevice, stream));

    float h_out[num_class];
    float* d_out = nullptr;
    checkRuntime(cudaMalloc(&d_out, sizeof(h_out)));

    // 明确当前推理 ， 使用的输入大小
    auto input_dims = execution_context->getBindingDimensions(0); // getBindingDimensions?
    input_dims.d[0] = in_batch;

    execution_context->setBindingDimensions(0, input_dims);
    float* bindings[] = { d_in, d_out };
    bool success = execution_context->enqueueV2((void**)bindings, stream, nullptr); // enqueueV2 ,将d_in的数据给到了d_out

    checkRuntime(cudaMemcpyAsync(h_out, d_out, sizeof(h_out), cudaMemcpyDeviceToHost));
    checkRuntime(cudaStreamSynchronize(stream));

    float* prob = h_out;
    int predict_label = std::max_element(prob, prob + num_class) - prob; // 预测类别下标
    auto labels = LoadLabels("/home/zqh/CODE/Cuda-TensorRT/learning_ws/src/tensorrtStudy/workspace/labels.imagenet.txt");
    auto predict_name = labels[predict_label];
    float confidence = prob[predict_label];
    printf("Predict: %s, confidence = %f, label = %d\n", predict_name.c_str(), confidence, predict_label);

    // 释放掉cuda上的内存空间
    checkRuntime(cudaStreamDestroy(stream));
    checkRuntime(cudaFreeHost(h_in));
    checkRuntime(cudaFree(d_in));
    checkRuntime(cudaFree(d_out));
}

int main(int argc, char** argv)
{

    if (argc == 2 && std::string(argv[1]) == "-s") {
        if (!BuildModel())
            return -1;
    }

    else if (argc == 2 && std::string(argv[1]) == "-d") {
        Inference();
    }

    return 0;
}
