#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sstream>
#include <unistd.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_rtsp_publisher");
    ros::NodeHandle nh;

    std::string image_topic = "/image_track_box"; // 替换为你的图像话题名称
    std::string rtsp_url = "rtsp://127.0.0.1:8554/nhy"; // 替换为实际的RTSP服务器URL

    cv::VideoWriter writer;
    cv::Size image_size;

    // 订阅图像话题的回调函数
    auto imageCallback = [&](const sensor_msgs::ImageConstPtr& msg) {
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        } catch (cv_bridge::Exception& e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        if (!writer.isOpened()) {
            image_size = cv_ptr->image.size();
            writer.open(rtsp_url, cv::VideoWriter::fourcc('H', '2', '6', '4'), 30, image_size, true);
            if (!writer.isOpened()) {
                ROS_ERROR("Failed to open VideoWriter");
                return;
            }
        }

        writer.write(cv_ptr->image);
    };

    ros::Subscriber image_subscriber = nh.subscribe<sensor_msgs::Image>(image_topic, 1, imageCallback);

    ros::spin();

    return 0;
}
