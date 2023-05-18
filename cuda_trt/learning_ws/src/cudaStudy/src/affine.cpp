#include <cuda_runtime.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

// #define checkRuntime(op) __check_cuda_runtime((op), #op, __FILE__, __LINE__)
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

void WarpAffineBilinear(
    uint8_t* src, int src_line_size, int src_width, int src_height,
    uint8_t* dst, int dst_line_size, int dst_width, int dst_height,
    uint8_t fill_value);

Mat WarpAffine_to_center_align(const Mat& image, const Size& size)
{
    Mat output(size, CV_8UC3);
    uint8_t* psrc_device = nullptr;
    uint8_t* pdst_device = nullptr;
    size_t src_size = image.cols * image.rows * 3;
    size_t dst_size = size.width * size.height * 3;

    checkRuntime(cudaMalloc(&psrc_device, src_size));
    checkRuntime(cudaMalloc(&pdst_device, dst_size));
    checkRuntime(cudaMemcpy(psrc_device, image.data, src_size, cudaMemcpyHostToDevice));

    WarpAffineBilinear(
        psrc_device, image.cols * 3, image.cols, image.rows,
        pdst_device, size.width * 3, size.width, size.height,
        100);

    checkRuntime(cudaPeekAtLastError()); // 检查核函数执行是否有问题
    checkRuntime(cudaMemcpy(output.data, pdst_device, dst_size, cudaMemcpyDeviceToHost));
    checkRuntime(cudaFree(psrc_device));
    checkRuntime(cudaFree(pdst_device));

    return output;
}

int main()
{
    Mat image = imread("/home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src/cudaStudy/pic/yq.png");
    Mat output = WarpAffine_to_center_align(image, Size(640, 640));
    imwrite("/home/zqh/PhoenixZ/Money_Cuda_TensorRT/learning_ws/src/cudaStudy/pic/output.png", output);
    printf("Done. save to output.jpg\n");
    return 0;
}