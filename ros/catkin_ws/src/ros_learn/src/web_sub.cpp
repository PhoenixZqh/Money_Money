#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace boost::beast::websocket;
using namespace boost::asio::ip;

cv::Mat receivedImage;

// WebSocket接收函数
void receiveImageViaWebSocket(stream<tcp::socket>& ws)
{
    try {
        // 接收图像数据
        boost::beast::multi_buffer buffer;
        ws.read(buffer);

        // 将图像数据转换为OpenCV图像
        std::string imageData(boost::beast::buffers_to_string(buffer.data()));
        std::vector<uchar> data(imageData.begin(), imageData.end());
        receivedImage = cv::imdecode(data, cv::IMREAD_COLOR);

        // 在窗口中显示图像
        cv::imshow("Received Image", receivedImage);
        cv::waitKey(1);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main()
{
    std::string host = "0.0.0.0";
    std::string port = "9002";
    std::string target = "/ws";

    try {
        boost::asio::io_context io_context;

        // 连接WebSocket服务器
        stream<tcp::socket> ws(io_context);
        tcp::resolver resolver(io_context);
        auto const results = resolver.resolve(host, port);
        boost::asio::connect(ws.next_layer(), results.begin(), results.end());
        ws.handshake(host, target);

        // 创建窗口用于显示接收到的图像
        cv::namedWindow("Received Image", cv::WINDOW_NORMAL);

        while (true) {
            // 接收并显示图像
            receiveImageViaWebSocket(ws);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
