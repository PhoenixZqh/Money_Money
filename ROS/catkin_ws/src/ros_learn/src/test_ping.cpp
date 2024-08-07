#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <iostream>
#include <string>
#include <array>
#include <regex>

std::string exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

double getPingDelay(const std::string &ip)
{
    std::string cmd = "ping -c 1 " + ip;
    std::string output = exec(cmd.c_str());

    std::regex re("time=([0-9]+\\.[0-9]+) ms");
    std::smatch match;
    if (std::regex_search(output, match, re) && match.size() > 1)
    {
        return std::stod(match.str(1));
    }
    else
    {
        throw std::runtime_error("Failed to parse ping output");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "ping_delay_publisher");
    ros::NodeHandle nh;
    ros::Publisher delay_pub = nh.advertise<std_msgs::Float64>("ping_delay", 1000);

    std::string ip = "10.88.105.47"; // 要ping的IP地址

    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        try
        {
            double delay = getPingDelay(ip);
            std_msgs::Float64 msg;
            msg.data = delay;
            delay_pub.publish(msg);
            // ROS_INFO("Ping delay to %s is %f ms", ip.c_str(), delay);
        }
        catch (const std::exception &e)
        {
            ROS_ERROR("Error: %s", e.what());
        }
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
