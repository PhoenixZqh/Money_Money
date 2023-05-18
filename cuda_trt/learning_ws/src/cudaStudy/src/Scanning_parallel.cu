#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

/*
1. 扫描并行化
2. 0,1,2,3,4,5,6,7 ,累计相加等于28
3. 算法的思想是以2的次方逐步增加
*/

__global__ void globalScan(float* d_in, float* d_out)
{
    int idx = threadIdx.x; // 获取线程ID号，每个线程代表一个数
    float out = 0.00f;

    d_out[idx] = d_in[idx]; // 先将输入数组复制给输出数组
    __syncthreads(); // 等所有的线程都完成工作

    // printf("sizeof d_In: %d\n", sizeof(d_in));

    for (int i = 1; i < sizeof(d_in); i *= 2) {
        if (idx - i >= 0) {
            out = d_out[idx] + d_out[idx - i];
        }
        __syncthreads();

        if (idx - i >= 0) {
            d_out[idx] = out;
            out = 0.00f;
        }

        __syncthreads();
        // printf("d_out:%f\n", d_out[idx]);
    }
    // printf("all:%f\n", d_out[7]);
}

int main(int argc, char** argv)
{
    const int arrSize = 8;
    const int arrBytes = arrSize * sizeof(float);

    float h_in[arrSize];
    float h_out[arrSize];

    for (int i = 0; i < arrSize; i++) {
        h_in[i] = float(i);
        // printf("h_in[%d]:%f\n", i, h_in[i]);
    }

    float* d_in;
    float* d_out;
    cudaMalloc((void**)&d_in, arrBytes);
    cudaMalloc((void**)&d_out, arrBytes); // 在GPU上分配内存空间

    cudaMemcpy(d_in, h_in, arrBytes, cudaMemcpyHostToDevice);

    globalScan<<<1, arrSize>>>(d_in, d_out);

    cudaMemcpy(h_out, d_out, arrBytes, cudaMemcpyDeviceToHost);

    for (int i = 0; i < arrSize; i++) {
        printf("[%d]得到的结果:%f\n", i, h_out[i]);
    }

    // cudaDeviceReset();
    return 0;
}