#include <ros/console.h>
#include <ros/ros.h>
#include <rosout_appender/rosout_appender.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "log_to_file_node");

    ros::NodeHandle nh;
    ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Info); // 设置日志级别
    ros::console::notifyLoggerLevelsChanged(); // 通知日志记录器级别已更改

    std::string log_path = "/path/to/logfile.log"; // 指定日志文件路径
    ros::console::LogAppenderPtr appender(new rosout_appender::RosoutAppender()); // 创建rosout日志记录器
    appender->setFilename(log_path); // 设置日志文件名
    ros::console::registerLogAppender(appender); // 注册日志记录器

    ROS_INFO("This is a log message."); // 记录日志信息

    return 0;
}
