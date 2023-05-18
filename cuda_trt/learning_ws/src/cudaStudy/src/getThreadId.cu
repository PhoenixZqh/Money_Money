#include <cudaStudy/cudaHelper.h>
#include <cuda_runtime.h>
#include <stdio.h>

__global__ void printThreadIndex(float* A, const int nx, const int ny)
{
    int ix = threadIdx.x + blockIdx.x * blockDim.x;
    int iy = threadIdx.y + blockIdx.y * blockDim.y;
    unsigned int idx = iy * nx + ix; // ix ,iy 是线程模型中的全局地址

    printf("thread_id(%d,%d) block_id(%d,%d) coordinate(%d,%d)"
           "global index %2d ival %2d\n",
        threadIdx.x, threadIdx.y,
        blockIdx.x, blockIdx.y, ix, iy, idx, A[idx]);
}

int main(int argc, char** argv)
{
    initDevice(0);
    int nx = 8, ny = 6;
    int nxy = nx * ny;
    int nBytes = nxy * sizeof(float);

    float* A_h = (float*)malloc(nBytes);
    initialData(A_h, nxy);
    printMatrix(A_h, nx, ny);

    float* A_d = NULL;
    CHECK(cudaMalloc((void**)&A_d, nBytes));
    cudaMemcpy(A_d, A_h, nBytes, cudaMemcpyHostToDevice);

    dim3 block(4, 2);
    dim3 grid((nx - 1) / block.x + 1, (ny - 1) / block.y + 1);
    printThreadIndex<<<grid, block>>>(A_d, nx, ny); // <<<gridDim(有多少个block), blockDim(有多少个thread)>>>

    CHECK(cudaDeviceSynchronize());
    cudaFree(A_d);
    free(A_h);

    cudaDeviceReset();
    return 0;
}
