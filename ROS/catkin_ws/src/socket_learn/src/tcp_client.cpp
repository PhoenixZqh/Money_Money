#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

int main() {
  int clientSocket;
  struct sockaddr_in serverAddr;
  char buffer[1024];

  // 创建TCP套接字
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  // 设置服务器地址结构
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(8880);                    // 服务器的端口号
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // 服务器的IP地址

  // 连接到服务器
  if (connect(clientSocket, (struct sockaddr*)&serverAddr,
              sizeof(serverAddr)) == -1) {
    perror("Error connecting to server");
    close(clientSocket);
    exit(EXIT_FAILURE);
  }

  while (true) {
    // 从用户输入获取消息
    std::string message;
    std::cout << "Enter a message to send (or 'quit' to exit): ";
    std::getline(std::cin, message);

    // 发送消息到服务器
    ssize_t sentLen = send(clientSocket, message.c_str(), message.length(), 0);
    if (sentLen == -1) {
      perror("Error sending data");
      close(clientSocket);
      exit(EXIT_FAILURE);
    }

    // 退出循环
    if (message == "quit") {
      break;
    }

    // 接收来自服务器的响应
    ssize_t recvLen = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (recvLen == -1) {
      perror("Error receiving response");
      close(clientSocket);
      exit(EXIT_FAILURE);
    }

    // 在接收到的数据后面添加一个 null 终止符，以便将其视为 C 字符串
    buffer[recvLen] = '\0';

    std::cout << "Received response from server: " << buffer << std::endl;
  }

  // 关闭客户端套接字
  close(clientSocket);

  return 0;
}
