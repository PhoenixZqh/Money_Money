#ifndef _TRT_BUILDER_HPP_
#define _TRT_BUILDER_HPP_

#include <functional>
#include <string>
#include <vector>

#include <tensorrtStudy/NvInfer.h>
#include <tensorrtStudy/NvInferPlugin.h>
#include <tensorrtStudy/NvOnnxParser.h>

using namespace std;
using namespace nvinfer1;

namespace TRT {
enum class Mode : int {
    FP32,
    FP16
};

const char* mode_string(Mode type);

bool compile(
    Mode mode,
    unsigned int maxBatchSize,
    const std::string& source,
    const std::string& saveto,
    const size_t maxWorkspaceSize = 1ul << 30);
};

class Logger : public ILogger {
public:
    virtual void log(Severity severity, const char* msg) noexcept override
    {

        if (severity == Severity::kINTERNAL_ERROR) {
            INFOE("NVInfer INTERNAL_ERROR: %s", msg);
            abort();
        } else if (severity == Severity::kERROR) {
            INFOE("NVInfer: %s", msg);
        } else if (severity == Severity::kWARNING) {
            INFOW("NVInfer: %s", msg);
        } else if (severity == Severity::kINFO) {
            INFOD("NVInfer: %s", msg);
        } else {
            INFOD("%s", msg);
        }
    }
};

#endif