#include <cuda.h>
#include <stdio.h>
#include <string.h>

/*
1. 采用宏定义在每次调用API前都检查初始化
2. 采用封装带参宏定义使代码更加清晰、好调试
*/

#define checkDriver(op) __check_cuda_driver((op), #op, __FILE__, __LINE__) // #op 加一个#是变成字符串的意思

bool __check_cuda_driver(CUresult code, const char* op, const char* file, int line)
{
    if (code != CUresult::CUDA_SUCCESS) {
        const char* err_name = nullptr;
        const char* err_msg = nullptr;
        cuGetErrorName(code, &err_name);
        cuGetErrorString(code, &err_msg);
        printf("%s:%d  %s failed. \n  code = %s, message = %s\n", file, line, op, err_name, err_msg);
        return false;
    }

    return true;
}

int main(int argc, char** argv)
{

    checkDriver(cuInit(0));

    // 测试获取当前cuda驱动的版本
    int driver_version = 0;
    if (!checkDriver(cuDriverGetVersion(&driver_version))) {
        return -1;
    }
    printf("Driver version is %d\n", driver_version);

    // 测试获取当前设备信息
    char device_name[100];
    CUdevice device = 0;
    checkDriver(cuDeviceGetName(device_name, sizeof(device_name), device));
    printf("Device %d name is %s\n", device, device_name);

    return 0;
}