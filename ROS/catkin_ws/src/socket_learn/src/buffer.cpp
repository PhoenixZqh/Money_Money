#include <iostream>
#include <cstdint>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

/**
 * ! 1. 测试struct转buffer
 * ! 2. 测试buffer转struct
 * ! 3. 测试拼接两个buffer
 * ! 4. 测试添加帧头、校验和
 * ! 5. 测试通过udp发送buffer
 * ! 6. 测试udp接收buffer
*/

struct MyData
{
    int m_a;
    int m_b;
    float m_c;
};

/**
 * 结构体转换到buffer
*/
std::vector<uint8_t> StructToBuffer(const MyData &data)
{
    std::cout << "mydata字节数: " << sizeof(MyData) << std::endl;
    std::vector<uint8_t> buffer(sizeof(MyData));
    std::memcpy(buffer.data(), &data, sizeof(MyData));

    return buffer;
}

/**
 * buffer转换到结构体
*/
MyData BuffeToStruct(const std::vector<uint8_t> &buffer)
{
    MyData data;
    std::memcpy(&data, buffer.data(), sizeof(MyData));
    return data;
}

/**
 * 拼接两个buffer
*/
std::vector<uint8_t> SpliceBuffer(const std::vector<uint8_t> &buffer1, const std::vector<uint8_t> &buffer2)
{
    std::vector<uint8_t> res;
    res.push_back(0XFD);
    res.insert(res.end(), buffer1.begin(), buffer1.end());
    res.insert(res.end(), buffer2.begin(), buffer2.end());

    uint16_t tmp = 0;
    for (auto byte : res)
    {
        tmp += byte;
    }

    res.push_back(static_cast<uint8_t>(tmp & 0xFF)); //低8位，高8位
    res.push_back(static_cast<uint8_t>((tmp >> 8) & 0xFF));

    return res;
}

/**
 * 读取buffer
*/
void ReadBuffer(const std::vector<uint8_t> &buff)
{
    std::cout << (int)buff[0] << std::endl;

    std::vector<uint8_t> buffer_data(buff.begin() + 1, buff.begin() + 13); //去掉头部和校验和
    std::vector<uint8_t> string_data(buff.begin() + 13, buff.begin() + 24);
    MyData test_data;
    std::memcpy(&test_data, buffer_data.data(), sizeof(MyData));

    std::string test_str(string_data.begin(), string_data.end());

    std::cout << test_data.m_a << " " << test_data.m_b << " " << test_data.m_c << std::endl;
    std::cout << test_str << std::endl;
}

/**
 * tcp发送buffer
*/
bool sendDataToServer(const char *serverIP, int serverPort, const std::vector<uint8_t> &buffer)
{
    // 创建套接字
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return false;
    }

    // 设置服务器地址信息
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    serverAddress.sin_addr.s_addr = inet_addr(serverIP);

    // 连接到服务器
    if (connect(clientSocket, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress)) == -1)
    {
        std::cerr << "Error connecting to server" << std::endl;
        close(clientSocket);
        return false;
    }

    // 发送缓冲区数据
    ssize_t sentBytes = send(clientSocket, buffer.data(), buffer.size(), 0);
    if (sentBytes == -1)
    {
        std::cerr << "Error sending data" << std::endl;
        close(clientSocket);
        return false;
    }
    else
    {
        std::cout << "Sent " << sentBytes << " bytes of data" << std::endl;
    }

    // 关闭套接字
    close(clientSocket);

    return true;
}

int main()
{
    MyData md = {10, 20, 3.3};
    std::vector<uint8_t> buffer = StructToBuffer(md);

    MyData md1 = BuffeToStruct(buffer);
    std::cout << md1.m_a << std::endl;

    std::string str1 = "test buffer";

    std::vector<uint8_t> buffer1(str1.begin(), str1.end()); //要提前分配大小

    std::vector<uint8_t> buff_two = SpliceBuffer(buffer, buffer1);
    ReadBuffer(buff_two);

    const char *serverIP = "127.0.0.1";
    int serverPort = 8008;

    if (sendDataToServer(serverIP, serverPort, buff_two))
    {
        std::cout << "Data sent successfully" << std::endl;
    }
    else
    {
        std::cerr << "Failed to send data" << std::endl;
    }

    return 0;
}