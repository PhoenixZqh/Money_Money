#include <arpa/inet.h>
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
    // 创建UDP套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    // 绑定套接字到特定的IP和端口
    sockaddr_in serverAddr {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9999); // 设置端口号
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, reinterpret_cast<const sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind socket." << std::endl;
        close(sockfd);
        return -1;
    }

    // 创建图像接收缓冲区
    unsigned char buffer[MAX_BUFFER_SIZE];

    while (true) {
        // 接收图像数据
        sockaddr_in clientAddr {};
        socklen_t clientAddrLen = sizeof(clientAddr);
        ssize_t receivedBytes = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE, 0, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);

        if (receivedBytes < 0) {
            std::cerr << "Failed to receive data." << std::endl;
            break;
        }

        // 将接收到的数据转换为OpenCV图像格式
        cv::Mat image(1, receivedBytes, CV_8UC1, buffer);
        cv::Mat decodedImage = cv::imdecode(image, cv::IMREAD_COLOR);

        // 检查图像是否成功解码
        if (decodedImage.empty()) {
            std::cerr << "Failed to decode image." << std::endl;
            break;
        }

        // 在这里可以对解码后的图像进行进一步处理
        cv::imshow("Received Image", decodedImage);
        cv::waitKey(1);
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}
