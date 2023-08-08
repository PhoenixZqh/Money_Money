#include "opencv2/opencv_modules.hpp"
#include <iostream>
#if defined(HAVE_OPENCV_CUDACODEC)
#include <algorithm>
#include <cv_bridge/cv_bridge.h>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/core/opengl.hpp>
#include <opencv2/cudacodec.hpp>
#include <opencv2/highgui.hpp>
#include <ros/ros.h>
#include <string>
#include <thread>
#include <vector>

using namespace std;

cv::Mat frame;
cv::cuda::GpuMat d_frame;

void FetchStream()
{
    const std::string fname
        = "/home/zqh/buck.mp4";

    cv::cuda::setDevice(0);

    cv::Ptr<cv::cudacodec::VideoReader> d_reader = cv::cudacodec::createVideoReader(fname);
    for (;;) {

        if (!d_reader->nextFrame(d_frame))
            break;

        d_frame.download(frame);

        cv::imshow("GPU", frame);

        if (cv::waitKey(3) > 0)
            break;
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "nhy_camera");

    thread stream_thread(FetchStream);
    ros::NodeHandle nh;
    ros::Publisher image_pub = nh.advertise<sensor_msgs::Image>("/nhy/gimbal_camera", 10);

    while (ros::ok()) {
        if (!frame.empty()) {
            sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
            msg->width = frame.cols;
            msg->height = frame.rows;
            msg->step = frame.cols * frame.channels();
            image_pub.publish(msg);
        }
        ros::spinOnce();
    }

    stream_thread.join();
    return 0;
}

#else

int main()
{
    std::cout << "OpenCV was built without CUDA Video decoding support\n"
              << std::endl;
    return 0;
}

#endif