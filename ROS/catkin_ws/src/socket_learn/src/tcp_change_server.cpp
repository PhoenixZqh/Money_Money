#include <iostream>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <opencv4/opencv2/opencv.hpp>
#include <string>

// 创建套接字
int createSocket()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
    }
    return serverSocket;
}

// 绑定套接字到地址和端口
bool bindSocket(int serverSocket, int port)
{
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    return bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) != -1;
}

// 监听连接
bool listenForConnections(int serverSocket)
{
    return listen(serverSocket, 5) != -1;
}

// 接受连接
int acceptConnection(int serverSocket)
{
    return accept(serverSocket, nullptr, nullptr);
}

// 读取并编码图像
std::vector<uint8_t> readAndEncodeImage(const std::string &filename)
{
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
    cv::resize(image, image, cv::Size(320, 320));
    if (image.empty())
    {
        std::cerr << "Error reading image: " << filename << std::endl;
        return std::vector<uint8_t>();
    }

    std::vector<uint8_t> encodedImage;
    cv::imencode(".jpg", image, encodedImage);

    return encodedImage;
}

std::vector<uint8_t> SpliceBuffer(const std::vector<uint8_t> &buffer1, const std::vector<uint8_t> &buffer2)
{
    std::vector<uint8_t> res;
    res.push_back(0XFD);
    res.insert(res.end(), buffer1.begin(), buffer1.end());
    res.insert(res.end(), buffer2.begin(), buffer2.end());

    size_t bodyLength = res.size() - 1;
    std::vector<uint8_t> bytes(4);
    bytes[0] = static_cast<uint8_t>(bodyLength & 0xFF);
    bytes[1] = static_cast<uint8_t>((bodyLength >> 8) & 0xFF);
    bytes[2] = static_cast<uint8_t>((bodyLength >> 16) & 0xFF);
    bytes[3] = static_cast<uint8_t>((bodyLength >> 24) & 0xFF);

    res.insert(res.begin() + 1, bytes[0]);
    res.insert(res.begin() + 2, bytes[1]);
    res.insert(res.begin() + 3, bytes[2]);
    res.insert(res.begin() + 4, bytes[3]);

    std::cout << bodyLength << std::endl;

    uint8_t tmp = 0;
    for (auto byte : res)
    {
        tmp += byte;
    }

    res.push_back(tmp);

    // std::cout << res.size() << " " << static_cast<int>(tmp) << std::endl;

    // int tmp = res.size();

    // res.insert(res.begin() + 1, tmp - 1);
    // std::cout << tmp << std::endl;

    // std::cout << "低: " << (int)static_cast<uint8_t>(tmp & 0xFF) << std::endl;
    // std::cout << "高: " << (int)static_cast<uint8_t>((tmp >> 8) & 0xFF) << std::endl;

    // res.push_back(static_cast<uint8_t>(res.size() & 0xFF));        //低8位
    // res.push_back(static_cast<uint8_t>((res.size() >> 8) & 0xFF)); //高8位

    return res;
}

// 发送数据的函数
bool sendDataToClient(int clientSocket, const std::vector<uint8_t> &data)
{
    ssize_t bytesSent = send(clientSocket, data.data(), data.size(), 0);

    if (bytesSent == -1)
    {
        std::cerr << "Error sending data" << std::endl;
        return false;
    }

    return true;
}

int main()
{
    // 创建套接字
    int serverSocket = createSocket();
    if (serverSocket == -1)
    {
        return -1;
    }

    // 绑定套接字到地址和端口
    try
    {
        if (!bindSocket(serverSocket, 8008))
        {
            std::cerr << "Error binding socket" << std::endl;
            close(serverSocket);
            return -1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // 监听连接
    if (!listenForConnections(serverSocket))
    {
        std::cerr << "Error listening for connections" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Server listening for connections..." << std::endl;

    // 接受连接
    int clientSocket = acceptConnection(serverSocket);
    if (clientSocket == -1)
    {
        std::cerr << "Error accepting connection" << std::endl;
        close(serverSocket);
        return -1;
    }

    std::cout << "Client connected" << std::endl;

    // 读取并发送图像
    std::string filename = "/home/data-jinshan/pic_fca/2.png"; // 请替换为实际图像路径
    std::vector<uint8_t> encodedImage = readAndEncodeImage(filename);

    std::string str = "test server";
    std::vector<uint8_t> str_buff(str.begin(), str.end());
    std::vector<uint8_t> res = SpliceBuffer(str_buff, encodedImage);

    // 发送图像数据给客户端
    if (!encodedImage.empty())
    {
        if (sendDataToClient(clientSocket, res))
        {
            // std::cout << "Image sent to client: " << res.size() << std::endl;
        }
    }

    // 关闭套接字
    close(clientSocket);
    close(serverSocket);

    return 0;
}
