#include <ctime>
#include <fstream>
#include <iostream>

void log_message(const std::string& message)
{
    std::ofstream logfile("/home/zqh/mylogfile.log", std::ios::app); // 打开日志文件并追加内容
    if (logfile.is_open()) {
        std::time_t current_time = std::time(nullptr);
        std::string time_str = std::asctime(std::localtime(&current_time));
        time_str.pop_back(); // 删除末尾的换行符

        logfile << "[" << time_str << "] " << message << std::endl; // 将日志消息写入文件
        logfile.close(); // 关闭日志文件
    }
}

int main()
{
    std::cout << "This is a console message." << std::endl;
    std::cerr << "This is an error message." << std::endl;

    log_message("This is a log message.");

    return 0;
}
