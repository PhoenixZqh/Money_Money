#include <ros/ros.h>
#include <std_msgs/String.h>
#include <cstdlib>
#include <cstdio>
#include <memory>
#include <string>

class BandwidthMonitor
{
public:
    BandwidthMonitor()
    {
        // 创建一个发布者
        pub_ = nh_.advertise<std_msgs::String>("bandwidth_data", 1000);
    }

    void run()
    {
        // 启动一个进程运行 ifstat
        std::string command = "ifstat -S 1 1"; // 每秒输出一次
        while (ros::ok())
        {
            // 读取 ifstat 输出
            std::string result = exec(command.c_str());

            // 创建消息并发布
            std_msgs::String msg;
            msg.data = result;
            pub_.publish(msg);

            // 等待一段时间
            ros::Duration(1.0).sleep(); // 每秒发布一次
        }
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher pub_;

    // 执行命令并返回输出
    std::string exec(const char *cmd)
    {
        std::array<char, 128> buffer;
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) return "popen() failed!";
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result += buffer.data();
        }
        return result;
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "bandwidth_monitor");
    BandwidthMonitor monitor;
    monitor.run();
    return 0;
}
