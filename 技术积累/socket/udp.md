# udp 客户端 & 服务端实现

## udp_server.cpp

```
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int udpSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char buffer[1024];

    // 创建UDP套接字
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // 服务器可以绑定到任何可用的网络接口
    serverAddr.sin_port = htons(8888); // 设置服务器监听的端口号

    // 将套接字绑定到服务器地址
    if (bind(udpSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding");
        close(udpSocket);
        exit(EXIT_FAILURE);
    }

    std::cout << "UDP server is listening on port 8888..." << std::endl;

    while (true) {
        // 接收来自客户端的数据
        ssize_t recvLen = recvfrom(udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (recvLen == -1) {
            perror("Error receiving data");
            close(udpSocket);
            exit(EXIT_FAILURE);
        }

        // 在接收到的数据后面添加一个 null 终止符，以便将其视为 C 字符串
        buffer[recvLen] = '\0';

        std::cout << "Received message from client: " << buffer << std::endl;

        // 在这里可以对接收到的数据进行处理，然后发送响应

        // 发送响应到客户端
        const char* response = "Hello, client!";
        ssize_t sentLen = sendto(udpSocket, response, strlen(response), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
        if (sentLen == -1) {
            perror("Error sending response");
            close(udpSocket);
            exit(EXIT_FAILURE);
        }
    }

    // 关闭套接字
    close(udpSocket);

    return 0;
}

```

## udp_client.cpp

```
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    int udpSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // 创建UDP套接字
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888); // 服务器的端口号
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 服务器的IP地址

    while (true) {
        // 从用户输入获取消息
        std::string message;
        std::cout << "Enter a message to send (or 'quit' to exit): ";
        std::getline(std::cin, message);

        // 发送消息到服务器
        ssize_t sentLen = sendto(udpSocket, message.c_str(), message.length(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        if (sentLen == -1) {
            perror("Error sending data");
            close(udpSocket);
            exit(EXIT_FAILURE);
        }

        // 退出循环
        if (message == "quit") {
            break;
        }

        // 接收来自服务器的响应
        ssize_t recvLen = recvfrom(udpSocket, buffer, sizeof(buffer), 0, nullptr, nullptr);
        if (recvLen == -1) {
            perror("Error receiving response");
            close(udpSocket);
            exit(EXIT_FAILURE);
        }

        // 在接收到的数据后面添加一个 null 终止符，以便将其视为 C 字符串
        buffer[recvLen] = '\0';

        std::cout << "Received response from server: " << buffer << std::endl;
    }

    // 关闭套接字
    close(udpSocket);

    return 0;
}

```

# UDP 传输图像示例

## udp_pub_image.cpp

```
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

```

## udp_sub_image.cpp

```
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

```
