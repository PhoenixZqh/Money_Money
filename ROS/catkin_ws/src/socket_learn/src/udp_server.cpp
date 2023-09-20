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
