#include <cuda.h>
#include <stdio.h>
#include <string.h>

/*
1. 什么是上下文？
    设备与特定进程相关连的所有状态称之为上下文；比如写了一段核函数对GPU的使用造成不同的状态（内存映射、分配、加载的code），
    上下文则保存所有的管理数据来控制和使用设备；
2. 上下文管理可以干哪些工作？
    a. 持有分配的内存列表
    b. 持有加载进该设备的kernel code
    c. cpu和GPU之间的unified memory

3. 如何管理上下文？
    a. 需手动开关，开始时cuCtxCreate()创建上下文，结束时cuCtxDestroy销毁上下文；
    b. 用cuDevicePrimaryCtxRetain()创建上下文更好
    c. cuCtxGetCurrent()获取当前上下文
    d. 可以使用堆栈管理多个上下文cuCtxPushCurrent()压入，cuCtxPopCurrent()推出
    e. 对ctxA使用cuCtxPushCurrent()和cuCtxCreate()都相当于将ctxA放到栈顶（让它成为current context）
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

    // 为设备创建上下文
    CUcontext ctxA = nullptr;
    CUcontext ctxB = nullptr;

    CUdevice device = 0;

    // 告诉某一块设备要在哪个地方创建ctxA管理数据
    checkDriver(cuCtxCreate(&ctxA, CU_CTX_SCHED_AUTO, device));
    checkDriver(cuCtxCreate(&ctxB, CU_CTX_SCHED_AUTO, device));
    printf("ctxA = %p\n", ctxA);
    printf("ctxB = %p\n", ctxB);

    // 获取当前上下文信息
    CUcontext current_context = nullptr;
    checkDriver(cuCtxGetCurrent(&current_context));
    printf("current_context = %p\n", current_context);

    // 使用上下文堆栈对设备管理多个上下文
    checkDriver(cuCtxPushCurrent(ctxA)); // 将这个 ctxA 压入CPU调用的thread上。专门用一个thread以栈的方式来管理多个contexts的切换
    checkDriver(cuCtxGetCurrent(&current_context)); // 获取current_context (即栈顶的context)
    printf("after pushing, current_context = %p\n", current_context);

    // 弹出当前content
    CUcontext popped_ctx = nullptr;
    checkDriver(cuCtxPopCurrent(&popped_ctx));
    checkDriver(cuCtxGetCurrent(&current_context));
    printf("after poping, popped_ctx = %p\n", popped_ctx); // 弹出的是ctxA
    printf("after poping, current_context = %p\n", current_context); // current_context是ctxB

    // 销毁上下文
    checkDriver(cuCtxDestroy(ctxA));
    checkDriver(cuCtxDestroy(ctxB));

    checkDriver(cuDevicePrimaryCtxRetain(&ctxA, device)); // 在 device 上指定一个新地址对ctxA进行管理
    printf("ctxA = %p\n", ctxA);
    checkDriver(cuDevicePrimaryCtxRelease(device));

    return 0;
}