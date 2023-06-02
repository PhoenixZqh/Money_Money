#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/Image.h>

using namespace boost::beast::websocket;
using namespace boost::asio::ip;

static const std::string base64Chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string base64Encode(const uchar* data, size_t length)
{
    std::string encoded;
    encoded.reserve((length + 2) / 3 * 4);

    for (size_t i = 0; i < length; i += 3) {
        uint32_t value = (data[i] << 16) + ((i + 1 < length) ? (data[i + 1] << 8) : 0) + ((i + 2 < length) ? data[i + 2] : 0);

        encoded.push_back(base64Chars[(value >> 18) & 0x3F]);
        encoded.push_back(base64Chars[(value >> 12) & 0x3F]);
        encoded.push_back((i + 1 < length) ? base64Chars[(value >> 6) & 0x3F] : '=');
        encoded.push_back((i + 2 < length) ? base64Chars[value & 0x3F] : '=');
    }

    return encoded;
}

// WebSocket发送函数
void sendImageViaWebSocket(const std::string& imageBase64)
{
    try {
        boost::asio::io_context io_context;

        std::string host = "0.0.0.0";
        std::string port = "9002";
        std::string target = "/ws";

        stream<tcp::socket> ws(io_context);
        tcp::resolver resolver(io_context);
        auto const results = resolver.resolve(host, port);
        boost::asio::connect(ws.next_layer(), results.begin(), results.end());
        ws.handshake(host, target);

        ws.write(boost::asio::buffer(imageBase64));

        ws.close(close_code::normal);

        io_context.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// 图像回调函数
void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    // 将ROS图像消息转换为OpenCV图像格式
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    // 将图像编码为Base64字符串
    std::vector<uchar> buffer;
    cv::imencode(".jpg", cv_ptr->image, buffer);
    std::string imageBase64 = base64Encode(buffer.data(), buffer.size());

    // 发送图像数据
    sendImageViaWebSocket(imageBase64);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_sender_node");
    ros::NodeHandle nh;

    ros::Subscriber image_sub = nh.subscribe("/image_track_box", 1, imageCallback);

    ros::spin();

    return 0;
}
