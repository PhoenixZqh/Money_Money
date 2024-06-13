#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_datatypes.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "yaw_to_quaternion");
    ros::NodeHandle nh;

    double yaw_angle = -106.f * 3.1415926 / 180.f; // 这里的yaw角度以弧度表示，假设值为1.0弧度

    // 创建四元数
    tf::Quaternion quaternion = tf::createQuaternionFromYaw(yaw_angle);

    // 将tf::Quaternion转换为geometry_msgs::Quaternion
    geometry_msgs::Quaternion quat_msg;
    tf::quaternionTFToMsg(quaternion, quat_msg);

    // 打印四元数
    ROS_INFO("Quaternion: x=%f, y=%f, z=%f, w=%f", quat_msg.x, quat_msg.y, quat_msg.z, quat_msg.w);

    return 0;
}
