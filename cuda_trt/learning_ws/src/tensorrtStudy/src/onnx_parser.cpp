#include <fstream>
#include <iostream>
#include <map>
#include <ros/ros.h>
#include <stdio.h>
#include <tensorrtStudy/NvInfer.h>
#include <tensorrtStudy/NvInferRuntime.h>
#include <tensorrtStudy/NvOnnxParser.h>
#include <tensorrtStudy/logging.h>

// static Logger gLogger;
using namespace std;
using namespace nvinfer1;
using namespace nvonnxparser;

inline const char* severity_string(nvinfer1::ILogger::Severity t)
{
    switch (t) {
    case nvinfer1::ILogger::Severity::kINTERNAL_ERROR:
        return "internal_error";
    case nvinfer1::ILogger::Severity::kERROR:
        return "error";
    case nvinfer1::ILogger::Severity::kWARNING:
        return "warning";
    case nvinfer1::ILogger::Severity::kINFO:
        return "info";
    case nvinfer1::ILogger::Severity::kVERBOSE:
        return "verbose";
    default:
        return "unknow";
    }
}

class TRTLogger : public nvinfer1::ILogger {
public:
    virtual void log(Severity severity, nvinfer1::AsciiChar const* msg) noexcept override
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

bool BuildModel()
{
    TRTLogger logger;

    // 1.定义builder、config、和network
    IBuilder* builder = createInferBuilder(logger);
    IBuilderConfig* config = builder->createBuilderConfig();
    INetworkDefinition* network = builder->createNetworkV2(1);

    // 2. 输入模型基本结构和输出
    IParser* parser = createParser(*network, logger); // 通过onnx parser 填充network；
    if (!parser->parseFromFile("src/tensorrtStudy/Model/demo.onnx", 1)) {
        ROS_INFO("Failed to parser demo.onnx");
        return false;
    }

    int max_batchSize = 10;
    config->setMaxWorkspaceSize(1 << 28);

    // 3. 关于profile
    auto profile = builder->createOptimizationProfile();
    auto input_tensor = network->getInput(0);
    auto input_channel = input_tensor->getDimensions().d[1];

    profile->setDimensions(input_tensor->getName(), OptProfileSelector::kMIN, Dims4(1, input_channel, 3, 3));
    profile->setDimensions(input_tensor->getName(), OptProfileSelector::kOPT, Dims4(1, input_channel, 3, 3));
    profile->setDimensions(input_tensor->getName(), OptProfileSelector::kMAX, Dims4(max_batchSize, input_channel, 5, 5));

    config->addOptimizationProfile(profile); // 添加到配置

    ICudaEngine* engine = builder->buildEngineWithConfig(*network, *config);
    assert(engine != nullptr);

    // 4. 序列化
    IHostMemory* model_data = engine->serialize();
    FILE* f = fopen("src/tensorrtStudy/Model/onnx_parser.engine", "wb");
    fwrite(model_data->data(), 1, model_data->size(), f);
    fclose(f);

    model_data->destroy();
    parser->destroy();
    engine->destroy();
    network->destroy();
    config->destroy();
    builder->destroy();
    ROS_INFO("Done.");
    return true;
}

int main()
{

    BuildModel();

    return 0;
}