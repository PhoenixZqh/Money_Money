#include <gtest/gtest.h>
#include <opencv4/opencv2/opencv.hpp>

/**
 * @brief 
 * 
 ** EXPECT_XXX第一个参数的值，即期待值
 ** EXPECT_XXX第二个参数的值，即实际值
 * 
*/

int add(int a, int b)
{
    return a + b;
}

int main(int argc, char **argv)
{
    // cv::CommandLineParser parser(argc, argv, "{h || print help msg}"
    //                                          "{a || num a}"
    //                                          "{b || num b}");

    // if (parser.has("h"))
    // {
    //     parser.printMessage();
    // }

    // int a = parser.get<int>("a");
    // int b = parser.get<int>("b");

    EXPECT_EQ(add(1, 1), 2); // PASS
    EXPECT_EQ(add(1, 1), 1) << "FAILED: EXPECT: 2, but given 1";

    return 0;
}