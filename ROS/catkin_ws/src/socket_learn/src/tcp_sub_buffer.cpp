#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <opencv4/opencv2/opencv.hpp>
#include <string>

// 接收数据的函数
bool receiveDataFromClient(int serverSocket, std::vector<uint8_t> &receivedData)
{
    // 接收数据
    constexpr size_t bufferSize = 65536; // 你可以根据实际需求调整缓冲区大小
    char buffer[bufferSize];

    ssize_t bytesRead = recv(serverSocket, buffer, bufferSize, 0);

    if (bytesRead == -1)
    {
        std::cerr << "Error receiving data" << std::endl;
        return false;
    }
    else if (bytesRead == 0)
    {
        std::cout << "Client disconnected" << std::endl;
        return false;
    }
    else
    {
        // 将接收的数据添加到 vector 中
        receivedData.insert(receivedData.end(), buffer, buffer + bytesRead);
        return true;
    }
}

int main()
{
    // 创建套接字
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return -1;
    }

    // 设置服务器地址信息
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8008); // 服务器端口
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // 绑定套接字到地址和端口
    if (bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) == -1)
    {
        std::cerr << "Error binding socket" << std::endl;
        close(serverSocket);
        return -1;
    }

    // 监听连接
    if (listen(serverSocket, 5) == -1)
    {
        std::cerr << "Error listening for connections" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Server listening for connections..." << std::endl;

    // 接受连接
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket == -1)
    {
        std::cerr << "Error accepting connection" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Client connected" << std::endl;

    // 接收数据
    std::vector<uint8_t> receivedData;
    while (receiveDataFromClient(clientSocket, receivedData))
    {
        // 在这里处理接收到的数据
        std::cout << receivedData.size() << std::endl;

        std::vector<uint8_t> img_data(receivedData.begin() + 13, receivedData.end() - 2);
        std::cout << "img_data: " << img_data.size() << std::endl;
        cv::Mat frame = cv::imdecode(img_data, cv::IMREAD_COLOR);
        int idx = 1;
        cv::imwrite("/home/data-jinshan/buffer/" + std::to_string(idx) + ".jpg", frame);

        // 清空接收缓冲区，准备接收下一批数据
        receivedData.clear();
    }

    // 关闭套接字
    close(clientSocket);
    close(serverSocket);

    return 0;
}
