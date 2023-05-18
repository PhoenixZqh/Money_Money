#include <cuda_runtime.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

/*

*/

using namespace std;

// 在全局内存上操作
__global__ void global_reduce_kernel(float* d_in, float* d_out)
{
    int myId = threadIdx.x + blockDim.x * blockIdx.x; // 所有线程放在一起你是第几号
    int tId = threadIdx.x; // 在当前block中你是第几号

    for (unsigned int s = blockDim.x / 2; s > 0; s >>= 1) {
        if (tId < s) {
            d_in[myId] += d_in[myId + s];
        }

        __syncthreads(); // 等待所有线程完成任务
    }

    if (tId == 0) {
        d_out[blockIdx.x] = d_in[myId]; // 第一个block的总和等于该block第一个线程的值，最后对折到只剩一个线程
    }

    // printf("gpu res:%f\n", d_out);
}

// 在共享内存上操作
__global__ void shared_reduce_kernel(float* d_in, float* d_out)
{
    extern __shared__ float data[]; // 创建共享内存

    int myId = threadIdx.x + blockDim.x * blockIdx.x; // 全局的线程索引？
    int tId = threadIdx.x; // 线程号

    data[tId] = d_in[myId];
    __syncthreads();

    for (unsigned int s = blockIdx.x / 2; s > 0; s >>= 1) {
        if (tId < s) {
            data[tId] += d_in[tId + s];
        }
        __syncthreads();
    }

    if (tId == 0) {
        d_out[blockIdx.x] = data[0];
    }
}

void reduce(float* d_in, float* d_intermediate, float* d_out, int size, bool useSharedMem)
{
    const int maxPerBlock = 1024;
    int threads = maxPerBlock;
    int block = size / maxPerBlock;

    if (useSharedMem) {
        shared_reduce_kernel<<<block, threads, threads * sizeof(float)>>>(d_in, d_intermediate);
    } else {
        global_reduce_kernel<<<block, threads>>>(d_in, d_intermediate);
    }

    // 将所有block的值相加
    threads = block;
    block = 1;

    if (useSharedMem) {
        shared_reduce_kernel<<<block, threads, threads * sizeof(float)>>>(d_intermediate, d_out);
    } else {
        global_reduce_kernel<<<block, threads>>>(d_intermediate, d_out);
    }
}

int main(int argc, char** argv)
{
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);

    if (deviceCount == 0) {
        fprintf(stderr, "err: no device supprot cuda");
        exit(EXIT_FAILURE);
    }

    int dev = 0;
    cudaSetDevice(dev);

    cudaDeviceProp devProps;
    if (cudaGetDeviceProperties(&devProps, dev) == 0) {
        printf("Using device % d \n", dev);
        printf("%s;global mem: %dB;compute v%d.%d;clock:%dkHZ\n",
            devProps.name, (int)devProps.totalGlobalMem, (int)devProps.major, (int)devProps.minor, (int)devProps.clockRate);
    }

    const int arrSize = 1 << 20;
    const int arrBytes = arrSize * sizeof(float);

    float h_in[arrSize];
    float sum = 0.0f;

    for (int i = 0; i < arrSize; i++) {
        // h_in[i] = -1.0f + (float)random() / ((float)RAND_MAX / 2.0f);
        h_in[i] = (i + 1) * 0.1;
        // printf("h_in:%f\n", h_in[i]);
        sum += h_in[i];
    }

    printf("sum:%f\n", sum);

    float* d_in;
    float* d_intermediate;
    float* d_out;

    cudaMalloc((void**)&d_in, arrBytes);
    cudaMalloc((void**)&d_intermediate, arrBytes);
    cudaMalloc((void**)&d_out, sizeof(float));

    cudaMemcpy(d_in, h_in, arrBytes, cudaMemcpyHostToDevice);
    int which_kernel = 0;
    if (argc == 2)
        which_kernel = atoi(argv[1]);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    switch (which_kernel) {
    case 0:
        printf("running gloabal reduce\n");
        cudaEventRecord(start, 0);
        // for (int i = 0; i < 100; i++) {
        cout << "d_in " << h_in[0] << endl;

        reduce(d_in, d_intermediate, d_out, arrSize, false);
        // }

        cudaEventRecord(stop, 0);
        break;

    case 1:
        printf("running shared reduce\n");
        cudaEventRecord(start, 0);
        // for (int i = 0; i < 100; i++) {
        reduce(d_in, d_intermediate, d_out, arrSize, true);
        // }

        cudaEventRecord(stop, 0);
        break;

    default:
        fprintf(stderr, "err:ran no kernel\n");
        exit(EXIT_FAILURE);
    }

    cudaEventSynchronize(stop);
    float elapsedTime;
    cudaEventElapsedTime(&elapsedTime, start, stop);
    elapsedTime /= 100.f;

    float h_out;
    cudaMemcpy(&h_out, d_out, sizeof(float), cudaMemcpyDeviceToHost); // 该函数是同步执行函数，在未完成数据的转移操作之前会锁死并一直占有CPU进程的控制权，所以不用再添加cudaDeviceSynchronize()函数

    printf("all:%f\n", h_out);

    printf("average time elapsed:%f\n", elapsedTime);

    cudaFree(d_in);
    cudaFree(d_intermediate);
    cudaFree(d_out);

    return 0;
}