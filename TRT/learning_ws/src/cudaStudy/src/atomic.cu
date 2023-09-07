#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

/*
    对同一块内存进行操作时，需要用到原子操作，不然就是乱序的
*/

__global__ void AtomicAdd(int* d_in)
{
    int Idx = blockDim.x * blockIdx.x + threadIdx.x;

    // atomicAdd(&d_in[Idx], 1);
    int test = atomicAdd(d_in, 1);
    printf("11111:%d", test);

    __syncthreads();

    printf("11111:%d", test);

    // d_in[Idx] += 1;
}

int main(int argc, char** argv)
{

    const int arrSize = 10;
    const int arrBytes = arrSize * sizeof(int);

    int h_in[arrSize];
    int h_out[arrSize];
    int* d_in = nullptr;

    for (int i = 0; i < arrSize; i++) {
        h_in[i] = i;
    }

    cudaMalloc((void**)&d_in, arrBytes); // 注意这里取地址

    cudaMemcpy(d_in, h_in, arrBytes, cudaMemcpyHostToDevice);

    int b = 10;
    int* a = &b;
    AtomicAdd<<<10, 100>>>(a);

    cudaMemcpy(h_out, d_in, arrBytes, cudaMemcpyDeviceToHost);

    for (int i = 0; i < arrSize; i++) {
        printf("h_out[%d]:%d\n", i, h_out[i]);
    }

    cudaFree(d_in);

    cudaDeviceReset();
    return 0;
}