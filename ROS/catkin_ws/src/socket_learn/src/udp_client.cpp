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
