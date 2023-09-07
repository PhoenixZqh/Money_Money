#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <tensorrtStudy/NvInfer.h>
#include <tensorrtStudy/NvInferRuntime.h>
#include <tensorrtStudy/logging.h>

static Logger gLogger;
using namespace std;
using namespace nvinfer1;

const int num_in = 1;
const int num_out = 1;

Weights MakeWeights(float* ptr, int n)
{
    Weights w;
    w.count = n; // 卷积核或者偏差的数量
    w.type = DataType::kFLOAT;
    w.values = ptr;
    return w;
}

bool BuildModel(int argc, char** argv)
{
    /******************************************创建实例化对象*************************************************************/
    IBuilder* builder = createInferBuilder(gLogger); // 创建builder
    IBuilderConfig* config = builder->createBuilderConfig(); // 创建config
    INetworkDefinition* network = builder->createNetworkV1(1); // 用INetworkDefinition来构建网络

    /*******************************************模型结构和输出************************************************************/
    float layer1_weight_values[] = {
        1.0, 2.0, 3.1,
        0.1, 0.1, 0.1,
        0.2, 0.2, 0.2
    };
    float layer1_bias_values[] = { 0.0 };

    ITensor* input = network->addInput("image", DataType::kFLOAT, Dims4(-1, num_in, -1, -1)); // 对于动态shape，只将in_channel设置为固定值，其他值为负
    Weights layer_weight = MakeWeights(layer1_weight_values, 9);
    Weights layer_bias = MakeWeights(layer1_bias_values, 1);

    // 卷积层
    auto layer1 = network->addConvolution(*input, num_out, DimsHW(3, 3), layer_weight, layer_bias);
    layer1->setPadding(DimsHW(1, 1));

    // 激活层
    auto prob = network->addActivation(*layer1->getOutput(0), ActivationType::kRELU);

    network->markOutput(*prob->getOutput(0));

    int maxBatchSize = 10;
    ROS_INFO("[work size]: %2.f MB", (1 << 28) / 1024.0f / 1024.0f);
    config->setMaxWorkspaceSize(1 << 28); // 用于layer实现临时存储，同时可以保存中间激活值

    /******************************************profile设置 （本小节重点部分）*********************************************/
    auto profile = builder->createOptimizationProfile();

    // 配置最小允许1x1x3x3
    profile->setDimensions(input->getName(), OptProfileSelector::kMIN, Dims4(1, num_in, 3, 3));
    profile->setDimensions(input->getName(), OptProfileSelector::kOPT, Dims4(1, num_in, 3, 3));

    // 配置最小允许1x1x5x5
    profile->setDimensions(input->getName(), OptProfileSelector::kMAX, Dims4(maxBatchSize, num_in, 5, 5));

    config->addOptimizationProfile(profile);

    ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);
    assert(engine != nullptr);

    /*******************************************序列化模型并保存*********************************************************/
    IHostMemory* model_data = engine->serialize();
    File* f fopen("dynamic.engine", "wb");
    fwrite(model_data->data(), 1, model_data->size(), f);
    fclose(f);

    model_data->destroy();
    model_data->destroy();
    engine->destroy();
    network->destroy();
    config->destroy();
    builder->destroy();

    std::cout << "DONE. " << std::endl;
}

vector<unsigned char> LoadFile(const string& file)
{
    ifstream in(file, ios::in | ios::binary);
    if (!in.is_open())
        return {};

    in.seekg(0, ios::end);
    size_t length = in.tellg();

    std::vector<unit8_t> data;
    if (length > 0) {
        in.seekg(0, ios::beg);
        data.resize(length);
        in.read((char*)&data[0], length);
    }

    in.close();
    return data;
}

void inference()
{
    /**************************************加载模型并序列化************************************************************/
    auto engine_data = LoadFile("dynamic.engine");
    IRuntime* runtime = createInferRuntime(gLogger);
    ICudaEngine* engine = runtime->deserializeCudaEngine(engine_data.data(), engine_data.size());
    assert(engine != nullptr);

    IExecutionContext* execution_context = engine->createExecutionContext();
    cudaStream_t stream = nullptr;

    cudaStreamCreate(&stream);

    /***************************************输入和输出****************************************************************/
    float h_in[] = {
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,

        // batch 1
        -1, 1, 1,
        1, 0, 1,
        1, 1, -1
    };

    float* d_in = nullptr;
    float* d_out = nullptr;

    int ib = 2;
    int iw = 3;
    int ih = 3;

    float h_out = [ib * iw * ih];

    cudaMalloc(&d_in, sizeof(h_in));
    cudaMalloc(&d_out, sizeof(h_out));
    cudaMemcpyAsync(d_in, h_in, sizeof(h_in), cudaMemcpyHostToDevice, stream);

    /******************************************推理******************************************************************/
    // 推理时要明确输入尺寸
    execution_context->setBindingDimensions(0, Dims4(ib, 1, ih, iw));
    float* bindings[] = { d_in, d_out };
    bool success = execution_context->enquequeV2((void**)bindings, stream, nullptr);
    cudaMemcpyAsync(h_out, d_out, sizeof(h_out), cudaMemcpyDeviceToHost, stream);
    cudaStreamSynchronize(stream);

    /*****************************************output *************************************************************/
    for (int i = 0; i < ib; i++) {
        for (int j = 0; j < iw * ih; j++) {
            std::cout << h_out[i * ih * iw * j] << "\t" << endl;
        }
    }

    ROS_INFO("clean memory");
    cudaFree(d_in);
    cudaFree(d_out);
    cudaStreamdestroy(stream);
    execution_context->destroy();
    engine->destroy();
    runtime->destroy();
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "arguments not right!" << std::endl;
        std::cerr << "./dynamic_shape -s   // serialize model to plan file" << std::endl;
        std::cerr << "./dynamic_shape -d   // deserialize plan file and run inference" << std::endl;
        return -1;
    }

    if (std::string(argv[1]) == "-s") {
        build_model();
    }

    else if (std::string(argv[1]) == "-d") {
        inference();
    }

    return 0;
}
