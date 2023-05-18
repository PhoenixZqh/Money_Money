#include <cudaStudy/cudaHelper.h>
#include <cuda_runtime.h>
#include <stdio.h>

/*
两个向量的加法
一个核函数只有一个grid， 一个grid有多个block， 一个block有多个线程
*/

// 在cpu上运行
void sumArrays(float* a, float* b, float* res, const int size)
{
    for (int i = 0; i < size; i += 4) {
        res[i] = a[i] + b[i];
        res[i + 1] = a[i + 1] + b[i + 1];
        res[i + 2] = a[i + 2] + b[i + 2];
        res[i + 3] = a[i + 3] + b[i + 3];
    }
}

// 核函数在GPU上运行
__global__ void sumArraysGpu(float* a, float* b, float* res)
{
    int i = threadIdx.x;
    res[i] = a[i] + b[i];
}

int main(int argc, char** argv)
{
    int dev = 0;
    cudaSetDevice(dev); // 设置想利用的设备，内存分配和核函数的启动都会在当前设备上

    int nElem = 32;
    printf("Vector size:%d\n", nElem);

    int nByte = sizeof(float) * nElem;
    float* a_h = (float*)malloc(nByte);
    float* b_h = (float*)malloc(nByte);
    float* res_h = (float*)malloc(nByte);
    float* res_gpu_h = (float*)malloc(nByte);

    // memset 用于特定值填充内存块
    memset(res_h, 0, nByte);
    memset(res_gpu_h, 0, nByte);

    float *a_d, *b_d, *res_d;
    // cudamalloc 返回值是CUDA中定义的一个错误代码
    CHECK(cudaMalloc((float**)&a_d, nByte)); // 分配设备端的内存空间, 指针是一个变量，既然是变量，就需要存储空间，存储的是指针变量的地址(想象void*),之后向这个地址中写入一个地址值（在GPU显存中）
    CHECK(cudaMalloc((float**)&b_d, nByte));
    CHECK(cudaMalloc((float**)&res_d, nByte));

    initialData(a_h, nElem);
    initialData(b_h, nElem);

    // cudaMemcpy用于在主机（Host）和设备（Device）之间往返的传递数据;   该函数是同步执行函数
    CHECK(cudaMemcpy(a_d, a_h, nByte, cudaMemcpyHostToDevice)); // dst ，src
    CHECK(cudaMemcpy(b_d, b_h, nByte, cudaMemcpyHostToDevice));

    dim3 block(nElem);
    dim3 grid(nElem / block.x);

    double iStart, iElaps;
    iStart = cpuSecond();
    sumArraysGpu<<<grid, block>>>(a_d, b_d, res_d);
    cudaDeviceSynchronize(); // 加上同步函数才是核函数的执行时间

    CHECK(cudaMemcpy(res_gpu_h, res_d, nByte, cudaMemcpyDeviceToHost));
    iElaps = cpuSecond() - iStart;
    printf("Execution configuration<<<%d,%d>>> Time elapsed %f sec\n", grid.x, block.x, iElaps);

    sumArrays(a_h, b_h, res_h, nElem);

    checkResult(res_h, res_gpu_h, nElem);
    cudaFree(a_d);
    cudaFree(b_d);
    cudaFree(res_d);

    free(a_h);
    free(b_h);
    free(res_h);
    free(res_gpu_h);

    return 0;
}