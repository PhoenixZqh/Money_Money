#include <ros/ros.h>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

int main()
{
    typedef Eigen::Matrix<float, 1, 8, Eigen::RowMajor> TEST;
    typedef Eigen::Matrix<float, 8, 8, Eigen::RowMajor> TEST1;

    TEST mtx;
    for (int i = 0; i < 8; i++)
    {
        mtx(i) = i;
    }

    TEST tmp = mtx.array().square();
    std::cout << tmp << "\n"
              << std::endl;

    TEST1 res = tmp.asDiagonal();

    std::cout << res << std::endl;

    return 0;
}
