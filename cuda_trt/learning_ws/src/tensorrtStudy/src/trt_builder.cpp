#include <chrono>
#include <iostream>
#include <sstream>

#include <cuda-tools.hpp>
#include <simple-logger.hpp>
#include <trt_builder.hpp>

#include <memory>
#include <string>

static Logger glogger;

namespace TRT {

static string join_dims(const vector<int>& dims)
{
    stringstream output;
    char buf[64];
    const char* fmts[] = { "%d", " x %d" };

    for (int i = 0; i < dims.size(); ++i) {
        snprintf(buf, sizeof(buf), fmts[i != 0], dims[i]);
        output << buf;
    }

    return output.str();
}

bool save_file(const string& file, const void* data, size_t length)
{
    FILE* f = fopen(file.c_str(), "wb");
    if (!f)
        return false;

    if (data && length > 0) {
        if (fwrite(data, 1, length, f) not_eq length) {
            fclose(f);
            return false;
        }
    }

    fclose(f);
    return true;
}

vstatic string format(const char* fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    char buffer[10000];
    vsprintf(buffer, fmt, vl);
    return buffer;
}

static string dims_str(const Dims& dims)
{
    return join_dims(vector<int>(dims.d, dims.d + dims.nbDims));
}

static const char* padding_mode_name(PaddingMode mode)
{
    switch (mode) {
    case PaddingMode::kEXPLICIT_ROUND_DOWN:
        return "explicit round down";
    case PaddingMode::kEXPLICIT_ROUND_UP:
        return "explicit round up";
    case PaddingMode::kSAME_UPPER:
        return "same supper";
    case PaddingMode::kSAME_LOWER:
        return "same lower";
    case PaddingMode::kCAFFE_ROUND_DOWN:
        return "caffe round down";
    case PaddingMode::kCAFFE_ROUND_UP:
        return "caffe round up";
    }
    return "Unknow padding mode";
}

static const char* pooling_type_name(PoolingType type)
{
    switch (type) {
    case PoolingType::kMAX:
        return "MaxPooling";
    case PoolingType::kAVERAGE:
        return "AveragePooling";
    case PoolingType::kMAX_AVERAGE_BLEND:
        return "MaxAverageBlendPooling";
    }
    return "Unknow pooling type";
}

static const char* activation_type_name(ActivationType activation_type)
{
    switch (activation_type) {
    case ActivationType::kRELU:
        return "ReLU";
    case ActivationType::kSIGMOID:
        return "Sigmoid";
    case ActivationType::kTANH:
        return "TanH";
    case ActivationType::kLEAKY_RELU:
        return "LeakyRelu";
    case ActivationType::kELU:
        return "Elu";
    case ActivationType::kSELU:
        return "Selu";
    case ActivationType::kSOFTSIGN:
        return "Softsign";
    case ActivationType::kSOFTPLUS:
        return "Parametric softplus";
    case ActivationType::kCLIP:
        return "Clip";
    case ActivationType::kHARD_SIGMOID:
        return "Hard sigmoid";
    case ActivationType::kSCALED_TANH:
        return "Scaled tanh";
    case ActivationType::kTHRESHOLDED_RELU:
        return "Thresholded ReLU";
    }
    return "Unknow activation type";
}

static string layer_type_name(ILayer* layer)
{
    switch (layer->getType()) {
    case LayerType::kCONVOLUTION:
        return "Convolution";
    case LayerType::kFULLY_CONNECTED:
        return "Fully connected";
    case LayerType::kACTIVATION: {
        IActivationLayer* act = (IActivationLayer*)layer;
        auto type = act->getActivationType();
        return activation_type_name(type);
    }
    case LayerType::kPOOLING: {
        IPoolingLayer* pool = (IPoolingLayer*)layer;
        return pooling_type_name(pool->getPoolingType());
    }
    case LayerType::kLRN:
        return "LRN";
    case LayerType::kSCALE:
        return "Scale";
    case LayerType::kSOFTMAX:
        return "SoftMax";
    case LayerType::kDECONVOLUTION:
        return "Deconvolution";
    case LayerType::kCONCATENATION:
        return "Concatenation";
    case LayerType::kELEMENTWISE:
        return "Elementwise";
    case LayerType::kPLUGIN:
        return "Plugin";
    case LayerType::kUNARY:
        return "UnaryOp operation";
    case LayerType::kPADDING:
        return "Padding";
    case LayerType::kSHUFFLE:
        return "Shuffle";
    case LayerType::kREDUCE:
        return "Reduce";
    case LayerType::kTOPK:
        return "TopK";
    case LayerType::kGATHER:
        return "Gather";
    case LayerType::kMATRIX_MULTIPLY:
        return "Matrix multiply";
    case LayerType::kRAGGED_SOFTMAX:
        return "Ragged softmax";
    case LayerType::kCONSTANT:
        return "Constant";
    case LayerType::kRNN_V2:
        return "RNNv2";
    case LayerType::kIDENTITY:
        return "Identity";
    case LayerType::kPLUGIN_V2:
        return "PluginV2";
    case LayerType::kSLICE:
        return "Slice";
    case LayerType::kSHAPE:
        return "Shape";
    case LayerType::kPARAMETRIC_RELU:
        return "Parametric ReLU";
    case LayerType::kRESIZE:
        return "Resize";
    }
    return "Unknow layer type";
}

static string layer_descript(ILayer* layer)
{
    switch (layer->getType()) {
    case LayerType::kCONVOLUTION: {
        IConvolutionLayer* conv = (IConvolutionLayer*)layer;
        return format("channel: %d, kernel: %s, padding: %s, stride: %s, dilation: %s, group: %d",
            conv->getNbOutputMaps(),
            dims_str(conv->getKernelSizeNd()).c_str(),
            dims_str(conv->getPaddingNd()).c_str(),
            dims_str(conv->getStrideNd()).c_str(),
            dims_str(conv->getDilationNd()).c_str(),
            conv->getNbGroups());
    }
    case LayerType::kFULLY_CONNECTED: {
        IFullyConnectedLayer* fully = (IFullyConnectedLayer*)layer;
        return format("output channels: %d", fully->getNbOutputChannels());
    }
    case LayerType::kPOOLING: {
        IPoolingLayer* pool = (IPoolingLayer*)layer;
        return format(
            "window: %s, padding: %s",
            dims_str(pool->getWindowSizeNd()).c_str(),
            dims_str(pool->getPaddingNd()).c_str());
    }
    case LayerType::kDECONVOLUTION: {
        IDeconvolutionLayer* conv = (IDeconvolutionLayer*)layer;
        return format("channel: %d, kernel: %s, padding: %s, stride: %s, group: %d",
            conv->getNbOutputMaps(),
            dims_str(conv->getKernelSizeNd()).c_str(),
            dims_str(conv->getPaddingNd()).c_str(),
            dims_str(conv->getStrideNd()).c_str(),
            conv->getNbGroups());
    }
    case LayerType::kACTIVATION:
    case LayerType::kPLUGIN:
    case LayerType::kLRN:
    case LayerType::kSCALE:
    case LayerType::kSOFTMAX:
    case LayerType::kCONCATENATION:
    case LayerType::kELEMENTWISE:
    case LayerType::kUNARY:
    case LayerType::kPADDING:
    case LayerType::kSHUFFLE:
    case LayerType::kREDUCE:
    case LayerType::kTOPK:
    case LayerType::kGATHER:
    case LayerType::kMATRIX_MULTIPLY:
    case LayerType::kRAGGED_SOFTMAX:
    case LayerType::kCONSTANT:
    case LayerType::kRNN_V2:
    case LayerType::kIDENTITY:
    case LayerType::kPLUGIN_V2:
    case LayerType::kSLICE:
    case LayerType::kSHAPE:
    case LayerType::kPARAMETRIC_RELU:
    case LayerType::kRESIZE:
        return "";
    }
    return "Unknow layer type";
}

static bool layer_has_input_tensor(ILayer* layer)
{
    int num_input = layer->getNbInputs();

    for (int i = 0; i < num_input; ++i) {
        auto input = layer->getInput[i];
        if (input == nullptr)
            continue;

        if (input->isNetworkInput()) {
            return true;
        }
    }

    return false;
}

static bool layer_has_output_tensor(ILayer* layer)
{
    int num_output = layer->getNbOutputs();

    for (int i = 0; i < num_output; ++i) {
        auto output = layer->getOutput[i];

        if (output == nullptr)
            continue;

        if (output->isNetworkOutput()) {
            return true;
        }
    }

    return false;
}

// 创建智能指针，避免builder、config、engine等忘记手动销毁
template <typename _T>
shared_ptr<_T> make_nvsahred(_T* ptr)
{
    return shared_ptr<_T>(ptr, [](_T* p) { p->destroy(); }); // lamda表达式是第二个参数，不写的话就用默认的delete；
}

}; // namespace trt_builder