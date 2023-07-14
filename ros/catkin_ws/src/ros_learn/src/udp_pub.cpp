#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <opencv2/opencv.hpp>
#include <sys/socket.h>

#define MAX_BUFFER_SIZE 65536

#ifdef _WIN32
#include <WinSock2.h> // for Windows
using SocketType = SOCKET;
#else
#include <unistd.h> // for Unix/Linux
using SocketType = int;
#define closesocket close
#endif

int main()
{
    // 读取图像文件
    cv::Mat image = cv::imread("/home/zqh/Pictures/1.png", cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Failed to open image file." << std::endl;
        return -1;
    }

    // 创建UDP套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    // 目标服务器的IP地址和端口号
    sockaddr_in serverAddr {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(1234); // 设置目标端口号
    serverAddr.sin_addr.s_addr = inet_addr("10.88.105.194"); // 设置目标IP地址

    // 将图像转换为JPEG格式
    std::vector<unsigned char> jpegBuffer;
    cv::imencode(".jpg", image, jpegBuffer);

    // 发送JPEG图像数据
    ssize_t bytesSent = sendto(sockfd, jpegBuffer.data(), jpegBuffer.size(), 0, reinterpret_cast<const sockaddr*>(&serverAddr), sizeof(serverAddr));
    if (bytesSent < 0) {
        std::cerr << "Failed to send data." << std::endl;
    } else {
        std::cout << "Total bytes sent: " << bytesSent << std::endl;
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}
