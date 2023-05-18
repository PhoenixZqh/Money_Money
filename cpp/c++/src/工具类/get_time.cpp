#include <chrono>
#include <iostream>

#include <chrono>
#include <ctime>
#include <iostream>

int main()
{
    // 获取当前时间戳
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    // 将时间戳转换为可读时间
    std::cout << "Current time: " << std::ctime(&now_time_t);

    return 0;
}
