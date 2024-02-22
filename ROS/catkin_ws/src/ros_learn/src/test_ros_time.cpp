#include <ros/ros.h>
#include <std_msgs/Float64.h>

ros::Time last_time;

void distanceCallback(const std_msgs::Float64::ConstPtr &msg)
{
    ros::Time current_time = ros::Time::now();
    ros::Duration duration = current_time - last_time;
    double delta_time = duration.toSec(); // 获取时间间隔（单位：秒）

    std::cout << "last_time: " << last_time << " "
              << "current_time: " << current_time << std::endl;

    last_time = current_time; // 更新上一个时间点

    // 输出时间间隔
    ROS_INFO("Time interval between messages: %f seconds", delta_time);

    // 在这里执行其他操作...
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "time_interval_node");
    ros::NodeHandle nh;

    // 订阅距离消息
    ros::Subscriber sub = nh.subscribe("distance_topic", 1, distanceCallback);

    // 设置上一个时间点为当前时间
    last_time = ros::Time::now();

    ros::spin();
    return 0;
}

#include <ros/ros.h>
#include <std_msgs/Float64.h>

ros::Time last_time;

void timerCallback(const ros::TimerEvent &)
{
    ros::Time current_time = ros::Time::now();
    ros::Duration duration = current_time - last_time;
    double delta_time = duration.toSec(); // 获取时间间隔（单位：秒）

    std::cout << "last_time: " << last_time << " "
              << "current_time: " << current_time << std::endl;

    last_time = current_time; // 更新上一个时间点

    // 输出时间间隔
    ROS_INFO("Time interval between callbacks: %f seconds", delta_time);

    // 在这里执行其他操作...
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "time_interval_node");
    ros::NodeHandle nh;

    // 创建定时器，设置回调函数和时间间隔（5秒）
    ros::Timer timer = nh.createTimer(ros::Duration(1), timerCallback);

    // 设置上一个时间点为当前时间
    last_time = ros::Time::now();

    ros::spin();
    return 0;
}
