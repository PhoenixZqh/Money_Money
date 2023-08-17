//
// Created by nhy on 2023/3/16.
//

#ifndef WEBSOCKET_VIDEO_PACKAGE_MQTT_CLIENT_HPP
#define WEBSOCKET_VIDEO_PACKAGE_MQTT_CLIENT_HPP

#include <functional>
#include <iostream>
#include <map>
#include <mqtt/client.h>
#include <ros/ros.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>
#include <thread>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include "nlohmann/json.hpp"
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

#include "MySocketServer.h"

class Mqtt_Client {

public:
    using MessageHandler = std::function<void(const std::string&, const std::string&)>;

private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_rgb;
    ros::Subscriber sub_depth;
    MySocketServer& mySocketServer;

    std::string topicName_rgb;

public:
    Mqtt_Client(ros::NodeHandle& nh, MySocketServer& mySocketServer, std::string topicName_rgb);

    void callback_depth(const sensor_msgs::ImageConstPtr& msg);

    void callback_rgb(const sensor_msgs::ImageConstPtr& msg);

    void cvMatToJPG(const cv::Mat& input, std::vector<uchar>& buf, int quality = 100);

    std::string vectorToBase64(const std::vector<uchar>& data);

    /**mqtt回调函数**/
    ~Mqtt_Client();
};

#endif // WEBSOCKET_VIDEO_PACKAGE_MQTT_CLIENT_HPP
