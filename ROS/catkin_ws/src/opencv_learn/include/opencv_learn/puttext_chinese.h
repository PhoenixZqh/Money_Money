#ifndef _PUTTEXT_CHINESE_H_
#define _PUTTEXT_CHINESE_H_

#include <iostream>
#include <opencv2/freetype.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;

class PutChineseText {
private:
    cv::Mat m_image;
    string m_text;
    string font_path = "/home/zqh/phoenixZ/Money_Money/ROS/catkin_ws/src/opencv_learn/font/STCAIYUN.TTF";

public:
    PutChineseText(cv::Mat image, string chinese_text);
    PutChineseText() = default;
    ~PutChineseText() = default;

    void showImage();
};

// cv::Mat Image = cv::imread("/home/zqh/phoenixZ/Money_Money/技术积累/img/nvidia-smi.png");
// string text = "测试中文";

#endif