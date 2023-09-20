#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

int main() {
  int serverSocket, clientSocket;
  struct sockaddr_in serverAddr, clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  char buffer[1024];

  // 创建TCP套接字
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    perror("Error creating socket");
    exit(EXIT_FAILURE);
  }

  // 设置服务器地址结构
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr =
      INADDR_ANY;  // 服务器可以绑定到任何可用的网络接口
  serverAddr.sin_port = htons(8880);  // 设置服务器监听的端口号

  // 将套接字绑定到服务器地址
  if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) ==
      -1) {
    perror("Error binding");
    close(serverSocket);
    exit(EXIT_FAILURE);
  }

  // 开始监听连接
  if (listen(serverSocket, 5) == -1) {
    perror("Error listening");
    close(serverSocket);
    exit(EXIT_FAILURE);
  }

  std::cout << "TCP server is listening on port 8880..." << std::endl;

  while (true) {
    // 接受客户端连接
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr,
                          &clientAddrLen);  // TCP不同于UDP的是需要先建立连接
    if (clientSocket == -1) {
      perror("Error accepting connection");
      close(serverSocket);
      exit(EXIT_FAILURE);
    }

    while (true) {
      // 接收来自客户端的数据
      ssize_t recvLen = recv(clientSocket, buffer, sizeof(buffer), 0);
      if (recvLen == -1) {
        perror("Error receiving data");
        close(clientSocket);
        break;  // 关闭当前连接，继续监听其他连接
      } else if (recvLen == 0) {
        // 客户端关闭了连接
        close(clientSocket);
        break;  // 关闭当前连接，继续监听其他连接
      }

      // 在接收到的数据后面添加一个 null 终止符，以便将其视为 C 字符串
      buffer[recvLen] = '\0';

      std::cout << "Received message from client: " << buffer << std::endl;

      // 在这里可以对接收到的数据进行处理，然后发送响应

      // 发送响应到客户端
      const char* response = "Hello, client!";
      ssize_t sentLen = send(clientSocket, response, strlen(response), 0);
      if (sentLen == -1) {
        perror("Error sending response");
      }
    }
  }

  // 关闭服务器套接字（通常不会执行到这里）
  close(serverSocket);

  return 0;
}
