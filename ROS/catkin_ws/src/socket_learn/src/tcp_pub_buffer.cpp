#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <ros/ros.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>
#include <sys/socket.h>
#include <unistd.h>
#include <opencv4/opencv2/opencv.hpp>
#include <vector>
#include <cstring>
#include <cstdint>

/**
 * @brief 实现将struct 和 图像拼接到一起，然后通过tcp将buffer发送出去
*/

struct MyData
{
    int m_a;
    int m_b;
    float m_c;
};

std::vector<uint8_t> SpliceBuffer(const std::vector<uint8_t> &buffer1, const std::vector<uint8_t> &buffer2)
{
    std::vector<uint8_t> res;
    res.push_back(0XFD);
    res.insert(res.end(), buffer1.begin(), buffer1.end());
    res.insert(res.end(), buffer2.begin(), buffer2.end());

    uint16_t tmp = 0;
    for (auto byte : res)
    {
        tmp += byte;
    }

    res.push_back(static_cast<uint8_t>(tmp & 0xFF)); //低8位，高8位
    res.push_back(static_cast<uint8_t>((tmp >> 8) & 0xFF));

    return res;
}

bool sendDataToServer(const char *serverIP, int serverPort, const std::vector<uint8_t> &buffer)
{
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }

    // 设置服务器地址信息
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    serverAddress.sin_addr.s_addr = inet_addr(serverIP);

    // 连接到服务器
    if (connect(clientSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) == -1)
    {
        std::cerr << "Error connecting to server" << std::endl;
        close(clientSocket);
        return false;
    }

    // 发送缓冲区数据
    ssize_t sentBytes = send(clientSocket, buffer.data(), buffer.size(), 0);
    if (sentBytes == -1)
    {
        std::cerr << "Error sending data" << std::endl;
        close(clientSocket);
        return false;
    }
    else
    {
        std::cout << "Sent " << sentBytes << " bytes of data" << std::endl;
    }

    // 关闭套接字
    close(clientSocket);

    return true;
}

int main()
{
    cv::Mat frame = cv::imread("/home/data-jinshan/pic_no3/5.png");
    cv::resize(frame, frame, cv::Size(480, 270));
    std::vector<uint8_t> img_buffer;
    std::vector<int> encodeParams;
    encodeParams.push_back(cv::IMWRITE_JPEG_QUALITY);
    encodeParams.push_back(50); // 设置较高的压缩质量，例如90
    cv::imencode(".jpg", frame, img_buffer, encodeParams);

    std::cout << img_buffer.size() << std::endl;

    MyData data = {10, 20, 30.0};
    std::vector<uint8_t> data_buffer(sizeof(MyData));
    std::memcpy(data_buffer.data(), &data, sizeof(MyData));

    std::vector<uint8_t> buff_two = SpliceBuffer(data_buffer, img_buffer);
    std::cout << "buffer_two: " << buff_two.size() << std::endl;

    const char *serverIP = "127.0.0.1";
    int serverPort = 8008;

    if (sendDataToServer(serverIP, serverPort, buff_two))
    {
        std::cout << "Data sent successfully" << std::endl;
    }
    else
    {
        std::cerr << "Failed to send data" << std::endl;
    }

    return 0;
}