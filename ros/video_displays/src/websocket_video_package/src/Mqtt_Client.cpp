// Created by nhy on 2023/3/16.
//

#include "Mqtt_Client.h"


using namespace std::chrono_literals;

Mqtt_Client::Mqtt_Client(ros::NodeHandle &nh, MySocketServer &socket, std::string topicName_rgb) : nh_(nh),
                                                                                                   mySocketServer(
                                                                                                           socket),
                                                                                                   topicName_rgb(
                                                                                                           topicName_rgb) {

    sub_rgb = nh_.subscribe(topicName_rgb, 10, &Mqtt_Client::callback_rgb, this);
    ros::Rate rate(20);
}

void Mqtt_Client::callback_rgb(const sensor_msgs::CompressedImageConstPtr &msg) {
    cv::Mat image = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR);
    std::vector<uchar> imageBuf;
    cv::Size newSize(640, 480);
    cv::resize(image, image, newSize);
    cvMatToJPG(image, imageBuf, 60);
    std::string base64_str = vectorToBase64(imageBuf);
    mySocketServer.sendMessage(base64_str);
}

void Mqtt_Client::cvMatToJPG(const cv::Mat &input, std::vector<uchar> &buf, int quality) {
    std::vector<int> encodeParams;
    encodeParams.push_back(cv::IMWRITE_JPEG_QUALITY);
    encodeParams.push_back(quality);
    cv::imencode(".jpg", input, buf, encodeParams);

}

std::string Mqtt_Client::vectorToBase64(const std::vector<uchar> &data) {
    // 创建BIO对象
    BIO *b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    // 创建BIO对象
    BIO *mem = BIO_new(BIO_s_mem());

    // 将BIO对象链接起来
    BIO_push(b64, mem);

    // 写入数据到BIO对象中
    BIO_write(b64, data.data(), static_cast<int>(data.size()));

    // 冲洗BIO对象
    BIO_flush(b64);

    // 获取BIO对象中的数据
    BUF_MEM *bptr = nullptr;
    BIO_get_mem_ptr(b64, &bptr);

    // 创建输出字符串
    std::string output(bptr->data, bptr->length);

    // 释放资源
    BIO_free_all(b64);

    return output;
}


Mqtt_Client::~Mqtt_Client() {
}

