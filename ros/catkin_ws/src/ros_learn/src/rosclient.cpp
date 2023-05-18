/**
 * 该例程将请求/spawn服务，服务数据类型turtlesim::Spawn
 */

#include <ros/ros.h>
#include <turtlesim/Spawn.h> //包含头文件

int main(int argc, char** argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "turtle_spawn");

    // 创建节点句柄
    ros::NodeHandle node;

    // 发现/spawn服务后，创建一个服务客户端，连接名为/spawn的service
    // 查询是否有名为spawn的服务，有则请求该服务，否则一直等待下去（阻塞型函数）
    ros::service::waitForService("/spawn");
    // 创建ServiceClient客户端，给spawn服务发送请求，<>中为请求的数据类型，()中为服务名
    ros::ServiceClient add_turtle = node.serviceClient<turtlesim::Spawn>("/spawn");

    // 初始化turtlesim::Spawn的请求数据（产生一只新的海龟）
    turtlesim::Spawn srv; // srv
    srv.request.x = 10.0; // x坐标
    srv.request.y = 10.0; // y坐标
    srv.request.name = "turtle2";

    // 请求服务调用
    ROS_INFO("Call service to spwan turtle[x:%0.6f, y:%0.6f, name:%s]", srv.request.x, srv.request.y, srv.request.name.c_str());
    add_turtle.call(srv); //阻塞型函数

    // 显示服务调用结果
    // ROS_INFO("Spwan turtle successfully [name:%s]", srv.response.name.c_str);

    return 0;
}
