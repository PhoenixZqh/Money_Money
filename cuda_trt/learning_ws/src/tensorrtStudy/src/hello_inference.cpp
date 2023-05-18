#include "tensorrtStudy/NvInfer.h"
#include "tensorrtStudy/NvInferRuntime.h"
#include "tensorrtStudy/logging.h"
#include <chrono> // for timing the execution
#include <fstream>
#include <iostream>
#include <map>

static Logger gLogger; // 用来捕获warning和info
const int INPUT_SIZE = 1;
const int OUTPUT_SIZE = 1;

using namespace nvinfer1;

/**********************************************1. 加载权重**********************************************/

std::map<std::string, Weights> loadWeights(const std::string file)
{
    std::cout << "[INFO]:loading model weights" << file << std::endl;
    std::map<std::string, Weights> weightMap;

    std::ifstream input(file); // 打开权重文件
    assert(input.is_open() && "[ERROR] : Unable to open weighit file");

    int32_t count;
    input >> count;
    assert(count > 0 && "Invalid Weight File");

    while (count--) {
        Weights wt { DataType::kFLOAT, nullptr, 0 };
        uint32_t size;

        std::string w_name;
        input >> w_name >> std::dec >> size; // 十进制
        wt.type = DataType::kFLOAT;

        uint32_t* val = reinterpret_cast<uint32_t*>(malloc(sizeof(val) * size)); // 分配空间之后再强制转换？

        for (uint32_t x = 0, y = size; x < y; ++x) {
            // Change hex values to uint32 (for higher values)
            input >> std::hex >> val[x]; // 十六进制
        }

        wt.values = val;
        wt.count = size;

        weightMap[w_name] = wt;
    }

    return weightMap;
}

/*********************************************2. 使用Builder 和 Configuration构建网络模型***************/
ICudaEngine* createMLPEngine(unsigned int maxBatchSize, IBuilder* builder, IBuilderConfig* config, DataType dt)
{
    std::cout << "[INFO]:creating MLP using TRT" << std::endl;

    // 加载网络模型
    std::map<std::string, Weights> weightMap = loadWeights("src/tensorrtStudy/Model/mlp.wts");

    // 创建空网络？
    INetworkDefinition* network = builder->createNetworkV2(0U);

    // 网络输入
    ITensor* data = network->addInput("data", DataType::kFLOAT, Dims3 { 1, 1, 1 });
    assert(data);

    // 网络全连接层
    IFullyConnectedLayer* fc1 = network->addFullyConnected(*data, 1, weightMap["linear.weight"], weightMap["linear.bias"]);
    assert(fc1);

    fc1->getOutput(0)->setName("out");
    network->markOutput(*fc1->getOutput(0));

    builder->setMaxBatchSize(1);
    config->setMaxWorkspaceSize(1 << 20);

    ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);
    assert(engine != nullptr); // 空的时候报异常

    network->destroy();

    for (auto& mem : weightMap) {
        free((void*)(mem.second.values));
    }

    return engine;
}

void APItoModel(unsigned int maxBatchSize, IHostMemory** modelStream)
{
    IBuilder* builder = createInferBuilder(gLogger); // 用于创建 IBuilder 类型的对象
    IBuilderConfig* config = builder->createBuilderConfig();
    ICudaEngine* engine = createMLPEngine(maxBatchSize, builder, config, DataType::kFLOAT);
    assert(engine != nullptr);

    (*modelStream) = engine->serialize();

    engine->destroy();
    builder->destroy();
}

void performSerialization()
{
    IHostMemory* modelStream { nullptr }; // 创建一个流？

    APItoModel(1, &modelStream);
    assert(modelStream != nullptr);

    std::cout << "[INFO]: writting engine into binary" << std::endl;

    std::ofstream p("src/tensorrtStudy/Model/mlp.engine", std::ios::binary);
    if (!p) {
        std::cerr << "could not open pan output file" << std::endl;
        return;
    }

    p.write(reinterpret_cast<const char*>(modelStream->data()), modelStream->size());

    modelStream->destroy();
    std::cout << "[INFO]: Successfully created TensorRT engine..." << std::endl;
    std::cout << "\n\tRun inference using `./mlp -d`" << std::endl;
}

void doInference(IExecutionContext& context, float* input, float* output, int batchSize)
{
    // 使用cuda上下文进行推理

    const ICudaEngine& engine = context.getEngine();

    assert(engine.getNbBindings() == 2);
    void* buffers[2];

    const int inputIndex = engine.getBindingIndex("data"); // 获取对应的输入输出索引
    const int outputIndex = engine.getBindingIndex("out");

    cudaMalloc(&buffers[inputIndex], batchSize * INPUT_SIZE * sizeof(float));
    cudaMalloc(&buffers[outputIndex], batchSize * OUTPUT_SIZE * sizeof(float));

    cudaStream_t stream;
    cudaStreamCreate(&stream); // 创建流

    cudaMemcpyAsync(buffers[inputIndex], input, batchSize * INPUT_SIZE * sizeof(float), cudaMemcpyHostToDevice, stream);
    context.enqueue(batchSize, buffers, stream, nullptr); // 对批处理异步执行推理
    cudaMemcpyAsync(output, buffers[outputIndex], batchSize * OUTPUT_SIZE * sizeof(float), cudaMemcpyDeviceToHost, stream);

    cudaStreamSynchronize(stream);

    cudaStreamDestroy(stream);
    cudaFree(buffers[inputIndex]);
    cudaFree(buffers[outputIndex]);
}

void performInference()
{
    char* trtModelStream { nullptr };
    size_t size { 0 };

    // read model from the engine file
    std::ifstream file("src/tensorrtStudy/Model/mlp.engine", std::ios::binary);
    if (file.good()) {
        file.seekg(0, file.end);
        size = file.tellg();
        file.seekg(0, file.beg);
        trtModelStream = new char[size];
        assert(trtModelStream);
        file.read(trtModelStream, size);
        file.close();
    }

    // create a runtime (required for deserialization of model) with NVIDIA's logger
    IRuntime* runtime = createInferRuntime(gLogger);
    assert(runtime != nullptr);

    // deserialize engine for using the char-stream
    ICudaEngine* engine = runtime->deserializeCudaEngine(trtModelStream, size, nullptr);
    assert(engine != nullptr);

    // create execution context -- required for inference executions
    IExecutionContext* context = engine->createExecutionContext();
    assert(context != nullptr);

    float out[1]; // array for output
    float data[1]; // array for input
    for (float& i : data)
        i = 12.0; // put any value for input

    // time the execution
    auto start = std::chrono::system_clock::now();

    // do inference using the parameters
    doInference(*context, data, out, 1);

    // time the execution
    auto end = std::chrono::system_clock::now();
    std::cout << "\n[INFO]: Time taken by execution: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

    // free the captured space
    context->destroy();
    engine->destroy();
    runtime->destroy();

    std::cout << "\nInput:\t" << data[0];
    std::cout << "\nOutput:\t";
    for (float i : out) {
        std::cout << i;
    }
    std::cout << std::endl;
}

int checkArgs(int argc, char** argv)
{
    /**
     * Parse command line arguments
     *
     * @param argc: argument count
     * @param argv: arguments vector
     * @return int: a flag to perform operation
     */

    if (argc != 2) {
        std::cerr << "[ERROR]: Arguments not right!" << std::endl;
        std::cerr << "./mlp -s   // serialize model to plan file" << std::endl;
        std::cerr << "./mlp -d   // deserialize plan file and run inference" << std::endl;
        return -1;
    }
    if (std::string(argv[1]) == "-s") {
        return 1;
    } else if (std::string(argv[1]) == "-d") {
        return 2;
    }
    return -1;
}

int main(int argc, char** argv)
{
    int args = checkArgs(argc, argv);
    if (args == 1)
        performSerialization();
    else if (args == 2)
        performInference();
    return 0;
}
