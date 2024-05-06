#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

/**
 * @brief opencv 用于命令行解析的类
 * ? has 判断是否包含
 * ? get 获取变量
*/

int main(int argc, char **argv)
{
    cv::CommandLineParser parser(argc, argv, "{help h|| }"
                                             "{a|| test number a}"
                                             "{b| |test string b}");

    if (parser.has("h"))
    {
        parser.printMessage();
    }

    int num = parser.get<int>("a");
    std::string str = parser.get<std::string>("b");
    std::cout << num << " " << str << std::endl;
    return 0;
}