/***************************************************************************************************************************
*uav_track.h 
*0.1版
*
* Author:  Niwh
*
* Update Time: 2021.12.21
*
* Introduction:  仅用于模拟的初期跟踪控制代码（only used in simlation）不可以直接使用在真机上，与真机不互通！
***************************************************************************************************************************/


#ifndef _UAV_TRACK_H_
#define _UAV_TRACK_H_

#include <ros/ros.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Vector3.h>
#include <dynamic_reconfigure/server.h>
#include <std_msgs/UInt16.h>
#include <chrono>
#include <algorithm>
#include <numeric>

#include <track8yolo/param_pidConfig.h>

#include "pidTrack.h"

#define HEIGHT_TAKEOFF 0.4

namespace uav
{
    enum StateOnTrack
    {
        IDLE = 0,
        FLY = 1,
        ONHEIGHT = 1 << 1,
        OVERHEIGHT = 1 << 2,
        ONFIND = 1 << 3,
        ONTRACK = 1 << 4,
        HOLDON = 1 << 5,
        BACK = 1 << 6,
        LAND = 1 << 7,
        XWARD = 1 << 8,
        XBACK = 257,
        YWARD = 1 << 9,
        YBACK=513,
        ROW = 1 << 10,

    };

    class Uav
    {
    public:
        explicit Uav(ros::NodeHandle &nh);
        ~Uav();
        Uav(const Uav &) = delete;
        Uav operator=(const Uav &) = delete;

        void RunTrack();

    private:
        void MsgUavState(const mavros_msgs::State::ConstPtr &statefromfcu);
        void MsgUavPose(const geometry_msgs::PoseStamped::ConstPtr &posefromfcu);
        void MsgUavVel(const geometry_msgs::TwistStamped::ConstPtr &velfromfcu);
        void MsgDectPos(const geometry_msgs::Vector3::ConstPtr &posefromdetect);
        void MsgGuiState(const std_msgs::UInt16::ConstPtr &msg);
        void ParamDynamicReconfig(track8yolo::param_pidConfig &config);
        // inline void CheckSafe(geometry_msgs::PoseStamped &pose);

        ros::NodeHandle nh_;
        ros::Publisher move_pub_;
        ros::Subscriber uavstate_sub_;
        ros::Subscriber dectpose_sub_;
        ros::Subscriber uavpose_sub_;
        ros::Subscriber uavvel_sub_;
        ros::Subscriber mode_sub_;
        dynamic_reconfigure::Server<track8yolo::param_pidConfig> server_;
        //dynamic_reconfigure::Server<track8yolo::param_pidConfig>::CallbackType fun_re_;
        //warning :can not use the method to arming a uav before the product had matured
        //Unless you need to take off a large number of drones at one time 
        //must use RC to arm and offboard the uav now
        ros::ServiceClient arming_client;
        ros::ServiceClient set_mode_client;


        mavros_msgs::State state_fcu_;
        geometry_msgs::PoseStamped pose_ori_;
        geometry_msgs::PoseStamped pose_;
        geometry_msgs::TwistStamped vel_;
        geometry_msgs::Vector3 repose_dect_;
        geometry_msgs::PoseStamped pose_target_;

        mavros_msgs::CommandBool arm_cmd_;
        mavros_msgs::SetMode offb_set_mode_;

        std::string node_name_;
        uint16_t mode_track_;
        uint16_t mode_last_;

        int frequency_control_;
        ros::Rate * rate_;
        double height_; //the height of uav when it is on tracking and flying
        // double height_max_; //the max safe height of uav
        double land_speed_; 

        pidTrack::PidTrack * algoX_; // the algorithm of X direction
        pidTrack::PidTrack * algoY_; // the algorithm of Y direction
        // pidTrack::PidTrack * algoW_; // the algorithm of yaw

        double x_ki_,x_kp_,x_kd_;
        double y_ki_,y_kp_,y_kd_;
        // double x_ki_,x_kp_,x_kd_;
        uint8_t lost_track_;
    };
}

#endif