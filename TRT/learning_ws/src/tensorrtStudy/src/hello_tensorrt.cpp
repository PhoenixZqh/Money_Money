#include "tensorrtStudy/NvInfer.h"
#include "tensorrtStudy/NvInferRuntime.h"
#include <iostream>
#include <stdio.h>

class TRTLogger : public nvinfer1::ILogger {
public:
    virtual void log(Severity severity, nvinfer1::AsciiChar const* msg) noexcept override
    {
        if (severity <= Severity::kVERBOSE) {
            printf("%d: %s\n", severity, msg);
        }
    }
};

nvinfer1::Weights make_weights(float* ptr, int n)
{
    nvinfer1::Weights w;
    w.count = n;
    w.type = nvinfer1::DataType::kFLOAT;
    w.values = ptr;
    return w;
}

int main()
{

    TRTLogger logger; // logger 用来捕捉warning 和 info

    /*****************************************1.定义builder，config, network**************************************/
    nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(logger); // builder 去build网络
    nvinfer1::IBuilderConfig* config = builder->createBuilderConfig(); // config->构建配置，指定tensorrt如何优化模型
    nvinfer1::INetworkDefinition* network = builder->createNetworkV2(1);

    /*****************************************2.输入，模型结构，输出************************************************/
    const int num_input = 3;
    const int num_output = 2;
    float layer1_weight_values[] = { 1.0, 2.0, 0.5, 0.1, 0.2, 0.5 };
    float layer1_bias_values[] = { 0.3, 0.8 };

    nvinfer1::ITensor* input = network->addInput("image", nvinfer1::DataType::kFLOAT, nvinfer1::Dims4(1, num_input, 1, 1));
    nvinfer1::Weights layer1_weight = make_weights(layer1_weight_values, 6);
    nvinfer1::Weights layer1_bias = make_weights(layer1_bias_values, 2);

    auto layer1 = network->addFullyConnected(*input, num_output, layer1_weight, layer1_bias); // 添加全连接层
    auto prob = network->addActivation(*layer1->getOutput(0), nvinfer1::ActivationType::kSIGMOID); // 添加激活层

    network->markOutput(*prob->getOutput(0)); // 这一句是什么意思？？？ 标记输出

    printf("Workspace Size = %.2f MB\n", (1 << 28) / 1024.0f / 1024.0f); // 256Mib

    config->setMaxWorkspaceSize(1 << 28);
    builder->setMaxBatchSize(1);

    /*****************************************3.生成engine文件***************************************************/
    nvinfer1::ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);
    if (engine == nullptr) {
        printf("build engine failed\n");
        return (-1);
    }

    /*****************************************4.序列化模型并存储*************************************************/
    nvinfer1::IHostMemory* model_data = engine->serialize();
    FILE* f = fopen("engine.trtmodel", "wb");
    fwrite(model_data->data(), 1, model_data->size(), f);
    fclose(f);

    model_data->destroy();
    engine->destroy();
    network->destroy();
    config->destroy();
    builder->destroy();

    printf("DONE.\n");

    return 0;
}