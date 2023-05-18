#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <string.h>

/*
1. 通过有参宏定义检查cuda driver 是否正常初始化、定位程序出错文件名、行数、以及错误信息
2. 宏定义中带有do while 保证程序的正确性
*/

#define checkDriver(op)                                                                                            \
    do {                                                                                                           \
        auto code = (op);                                                                                          \
        if (code != CUresult::CUDA_SUCCESS) {                                                                      \
            const char* err_name = nullptr;                                                                        \
            const char* err_msg = nullptr;                                                                         \
            cuGetErrorName(code, &err_name);                                                                       \
            cuGetErrorString(code, &err_msg);                                                                      \
            printf("%s:%d  %s failed. \n  code = %s, message = %s\n", __FILE__, __LINE__, #op, err_name, err_msg); \
            return -1;                                                                                             \
        }                                                                                                          \
    } while (0)

int main(int argc, char** argv)
{

    cuInit(2); // 初始化flag设置为0
    checkDriver(cuInit(0)); // cuda driver需要做显式的初始化cuInit(0), 不然其他API返回CUDA_ERROR_NOT_INITIALIZED

    int driverVersion = 0;
    checkDriver(cuDriverGetVersion(&driverVersion)); // 测试cuda版本
    printf("Driver version is %d\n", driverVersion);

    char deviceName[100];
    CUdevice device = 0;
    checkDriver(cuDeviceGetName(deviceName, sizeof(deviceName), device)); // 测试当前设备信息
    printf("Device %d name is %s\n", device, deviceName);

    return 0;
}