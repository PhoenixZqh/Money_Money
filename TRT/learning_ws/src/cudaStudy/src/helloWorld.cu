#include <cuda.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

__global__ void hello_world(void) //__global__ 告诉编译器这个是个可以在设备上执行的核函数
{

    printf("GPU: Hello world!\n");
}

int main(int argc, char** argv)
{

    printf("CPU: Hello world11111111111111111!\n");

    hello_world<<<2, 10>>>(); //执行2个10次
    cudaDeviceReset(); //功能相当于告诉主机线程，等GPU上的程序运行完了之后再退出

    return 0;
}