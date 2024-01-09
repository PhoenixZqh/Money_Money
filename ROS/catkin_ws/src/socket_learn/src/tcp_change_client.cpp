#include <iostream>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <opencv4/opencv2/opencv.hpp>

// 创建套接字
int createSocket()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
    }
    return clientSocket;
}

// 连接到服务器
bool connectToServer(int clientSocket, const std::string &serverIP, int serverPort)
{
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    serverAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());

    return connect(clientSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) != -1;
}

// 接收数据的函数
bool receiveDataFromServer(int clientSocket, std::vector<uint8_t> &receivedData)
{
    // 接收数据
    constexpr size_t bufferSize = 65536; // 你可以根据实际需求调整缓冲区大小
    char buffer[bufferSize];

    ssize_t bytesRead = recv(clientSocket, buffer, bufferSize, 0);

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
    int clientSocket = createSocket();
    if (clientSocket == -1)
    {
        return -1;
    }

    // 连接到服务器
    if (!connectToServer(clientSocket, "127.0.0.1", 8008))
    {
        std::cerr << "Error connecting to server" << std::endl;
        close(clientSocket);
        return -1;
    }

    std::cout << "Connected to server" << std::endl;

    std::vector<uint8_t> receivedData;

    while (receiveDataFromServer(clientSocket, receivedData))
    {
        std::cout << (int)receivedData[0] << " " << (int)receivedData[1] << " " << (int)receivedData[2] << " " << (int)receivedData[3] << " " << (int)receivedData[4] << std::endl;

        std::vector<uint8_t> img_buff(receivedData.begin() + 16, receivedData.end() - 1);

        cv::Mat frame = cv::imdecode(img_buff, cv::IMREAD_COLOR);
        int idx = 6;
        cv::imwrite("/home/data-jinshan/buffer/" + std::to_string(idx) + ".jpg", frame);

        // 清空接收缓冲区，准备接收下一批数据
        receivedData.clear();
    }

    // 关闭套接字
    close(clientSocket);

    return 0;
}
