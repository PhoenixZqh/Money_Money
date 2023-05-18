#include <iostream>
#include <stdio.h>
#include <string.h>

/*

*/
using namespace std;

__global__ void square(float* d_in, float* d_out)
{
    int idx = threadIdx.x; //.x表示当前线程号

    float f = d_in[idx];
    d_out[idx] = f * f * f;
}

int main(int argc, char** argv)
{

    const int arr_size = 8;
    const int arr_bytes = arr_size * sizeof(float);

    float h_in[arr_size];

    for (int i = 0; i < arr_size; i++) {
        h_in[i] = float(i);
    }

    float h_out[arr_size];

    float* d_in;
    float* d_out;

    cudaMalloc((void**)&d_in, arr_bytes);
    cudaMalloc((void**)&d_out, arr_bytes);

    cudaMemcpy(d_in, h_in, arr_bytes, cudaMemcpyHostToDevice);

    square<<<1, 8>>>(d_in, d_out);

    cudaMemcpy(h_out, d_out, arr_bytes, cudaMemcpyDeviceToHost);

    for (int i = 0; i < arr_size; i++) {
        cout << h_out[i] << endl;
    }

    cudaFree(d_in);
    cudaFree(d_out);

    return 0;
}