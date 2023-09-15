#include <opencv_learn/puttext_chinese.h>

PutChineseText::PutChineseText(cv::Mat image, string chinese_text)
    : m_image(image)
    , m_text(chinese_text)
{
}

void PutChineseText::showImage()
{
    // cv::Point center_pos(50, 50);

    // cv::putText(m_image, m_text, center_pos, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar { 255, 255, 255 }, 2);

    // cv::imshow("test_chinese", m_image);
    // cv::waitKey(10000000);

    cv::Ptr<cv::freetype::FreeType2> ft2 = cv::freetype::createFreeType2();
    ft2->loadFontData("/home/zqh/phoenixZ/Money_Money/ROS/catkin_ws/src/opencv_learn/font/simsun.ttc", 0);
    ft2->putText(m_image, m_text, cv::Point(10, 50), 10, cv::Scalar(0, 255, 0), 1, 4, true);
    cv::imshow("test_chinese", m_image);
    cv::waitKey(10000000);
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "请输入图像路径" << argv[0] << endl;
    }

    cv::Mat image = cv::imread(argv[1]);
    string text = "行人";

    PutChineseText pct(image, text);
    pct.showImage();

    return 0;
}