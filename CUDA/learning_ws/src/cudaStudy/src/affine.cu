#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <string.h>

/*
实现仿射变换（旋转、平移、缩放）
1. 根据src的尺寸、dst的尺寸计算src 到 dst 的矩阵关系 I2D
2. 根据I2D矩阵求逆可以得到dst 到 src 的矩阵关系 D2I
3. 根据D2I， 可以求得，dst上当前点在src上的位置
4. 位置已知，可以根据双线性插值求得该点的值
*/

#define min(a, b) ((a) < (b) ? (a) : (b))
#define num_threads 512

typedef unsigned char uint8_t;
struct Size {
    int m_width = 0;
    int m_height = 0;

    Size() = default;
    Size(int w, int h)
        : m_width(w)
        , m_height(h)
    {
    }
};

struct AffineMatrix {

    float I2D[6];
    float D2I[6];

    /*********************************************求逆矩阵**************************************************/
    void InvertAffineTransform(float imat[6], float omat[6])
    {
        float i00 = imat[0];
        float i01 = imat[1];
        float i02 = imat[2];
        float i10 = imat[3];
        float i11 = imat[4];
        float i12 = imat[5];

        // 计算行列式
        float D = i00 * i11 - i01 * i10;
        D = D != 0 ? 1.0 / D : 0;

        // 计算剩余的伴随矩阵除以行列式
        float A11 = i11 * D;
        float A22 = i00 * D;
        float A12 = -i01 * D;
        float A21 = -i10 * D;
        float b1 = -A11 * i02 - A12 * i12;
        float b2 = -A21 * i02 - A22 * i12;
        omat[0] = A11;
        omat[1] = A12;
        omat[2] = b1;
        omat[3] = A21;
        omat[4] = A22;
        omat[5] = b2;
    }

    /*********************************************计算I2D*************************************************/
    void ComputeI2D(const Size& from, const Size& to)
    {
        float scale_x = to.m_width / (float)from.m_width;
        float scale_y = to.m_height / (float)from.m_height;

        float scale = min(scale_x, scale_y); // 不能取最大，防止越界

        I2D[0] = scale;
        I2D[1] = 0;
        I2D[2] = -scale * from.m_width * 0.5 + to.m_width * 0.5 - 0.5;

        I2D[3] = 0;
        I2D[4] = scale;
        I2D[5] = -scale * from.m_height * 0.5 + to.m_height * 0.5 + scale * 0.5 - 0.5;

        InvertAffineTransform(I2D, D2I); // 求解逆矩阵是为了找到dst对应src上的位置
    }
};

/*********************************************计算dst上的点对应在src上的位置*****************************/
__device__ void FindPosSrc(float* matrix, int x, int y, float* src_x, float* src_y)
{
    *src_x = matrix[0] * x + matrix[1] * y + matrix[2];
    *src_y = matrix[3] * x + matrix[4] * y + matrix[5];
}

/*********************************************双线性插值确认这个点的值************************************/
__global__ void Warp_Affine_Bilinear_Kernel(
    uint8_t* src, int src_line_size, int src_width, int src_height,
    uint8_t* dst, int dst_line_size, int dst_width, int dst_height,
    uint8_t fill_value, AffineMatrix matrix)
{
    int idx = blockDim.x * blockIdx.x + threadIdx.x; // 两个维度上的索引
    int idy = blockDim.y * blockIdx.y + threadIdx.y;

    if (idx >= dst_width || idy >= dst_height) // 超出边界
        return;

    float c0 = fill_value, c1 = fill_value, c2 = fill_value;
    float src_x = 0;
    float src_y = 0;
    FindPosSrc(matrix.D2I, idx, idy, &src_x, &src_y);

    if (src_x < -1 || src_x >= src_width || src_y < -1 || src_y >= src_height) {

        // 这里我的理解是，该像素点周围的四个点 (x_low,y_low),(x_high,y_low),(x_low,y_high),(x_high,y_high)
        // 如果src_x < -1, x_low取整为-1,超出边界，要保证x_low最小为0； y方向上是一致的
    }

    else {
        int y_low = floorf(src_y);
        int x_low = floorf(src_x);
        int y_high = y_low + 1;
        int x_high = x_low + 1;

        uint8_t values[] = { fill_value, fill_value, fill_value }; // 超出边界的填充值

        float lx = src_x - x_low;
        float ly = src_y - y_low;
        float hx = 1 - lx;
        float hy = 1 - ly;

        float w1 = hx * hy;
        float w2 = lx * hy;
        float w3 = hx * ly;
        float w4 = lx * ly;

        uint8_t* v1 = values; // 指针指向的是地址，这里是给周围的四个点赋初值
        uint8_t* v2 = values;
        uint8_t* v3 = values;
        uint8_t* v4 = values;

        if (y_low >= 0) {
            if (x_low >= 0) {
                v1 = src + y_low * src_line_size + x_low * 3; // src_line_size表示图像宽度x3；
            }

            if (x_high < src_width) {
                v2 = src + y_low * src_line_size + x_high * 3;
            }
        }

        if (y_high < src_height) {
            if (x_low >= 0) {
                v3 = src + y_high * src_line_size + x_low * 3;
            }

            if (x_low < src_width) {
                v4 = src + y_high * src_line_size + x_high * 3;
            }
        }

        c0 = floorf(w1 * v1[0] + w2 * v2[0] + w3 * v3[0] + w4 * v4[0] + 0.5f);
        c1 = floorf(w1 * v1[1] + w2 * v2[1] + w3 * v3[1] + w4 * v4[1] + 0.5f);
        c2 = floorf(w1 * v1[2] + w2 * v2[2] + w3 * v3[2] + w4 * v4[2] + 0.5f);

        uint8_t* pdst = dst + idy * dst_line_size + idx * 3;
        pdst[0] = c0;
        pdst[1] = c1;
        pdst[2] = c2;
    }
}

void WarpAffineBilinear(
    uint8_t* src, int src_line_size, int src_width, int src_height,
    uint8_t* dst, int dst_line_size, int dst_width, int dst_height,
    uint8_t fill_value)
{
    dim3 block_size(32, 32);
    dim3 grid_size((dst_width + 31) / 32, (dst_height + 31) / 32);

    AffineMatrix affine;
    affine.ComputeI2D(Size(src_width, src_height), Size(dst_width, dst_height));

    Warp_Affine_Bilinear_Kernel<<<grid_size, block_size, 0, nullptr>>>( //<<<gridsize,blocksize,共享内存字节数，流>>>
        src, src_line_size, src_width, src_height,
        dst, dst_line_size, dst_width, dst_height,
        fill_value, affine);
}
