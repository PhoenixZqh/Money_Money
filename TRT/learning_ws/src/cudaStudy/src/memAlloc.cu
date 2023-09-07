#include <cuda.h>
#include <stdio.h>
#include <string.h>

/*

*/

#define checkDriver(op) __check_cuda_driver((op), #op, __FILE__, __LINE__)

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

    // 创建上下文
    CUcontext context = nullptr;
    CUdevice device = 0;
    checkDriver(cuCtxCreate(&context, CU_CTX_SCHED_AUTO, device));
    printf("context=%p\n", context);

    // 向设备要一个100字节大小的线性内存，并返回其地址
    CUdeviceptr device_memPtr = 0;
    checkDriver(cuMemAlloc(&device_memPtr, 100));
    printf("device memory Pointer=%p\n", device_memPtr);

    // 二级指针向host要一个100字节大小的锁页内存
    float* host_page_lock_memPtr = nullptr;
    checkDriver(cuMemAllocHost((void**)&host_page_lock_memPtr, 100));
    printf("host_page_lock_memPtr=%p\n", host_page_lock_memPtr);

    // 向分页内存上放数据（在cpu上）,可以让GPU快速读取
    host_page_lock_memPtr[0] = 111;
    printf("host_page_lock_memPtr[0]=%f\n", host_page_lock_memPtr[0]);

    float new_val = 222;
    checkDriver(cuMemsetD32((CUdeviceptr)host_page_lock_memPtr, *(int*)&new_val, 1));
    printf("after change,host_page_lock_memPtr[0]=%f\n", host_page_lock_memPtr[0]);

    // 释放内存
    checkDriver(cuMemFreeHost(host_page_lock_memPtr));

    cudaDeviceReset();
    return 0;
}