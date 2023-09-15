/***************************************************************************************************************************
*uav_track.cpp
*0.1版
*
* Author:  Niwh
*
* Update Time: 2021.12.21
*
* Introduction:  仅用于模拟的初期跟踪控制代码（only used in simlation）不可以直接使用在真机上，与真机不互通！
***************************************************************************************************************************/

#include "uav_track.h"

namespace uav
{
    Uav::Uav(ros::NodeHandle &nh) : nh_(nh)
    {
        lost_track_ = 0;
        node_name_ = ros::this_node::getName();
        nh_.param<double>(node_name_ + "/height", height_, 10.0);
        nh_.param<int>(node_name_ + "/hz_control", frequency_control_, 60);
        nh_.param<double>(node_name_ + "/land_speed", land_speed_, 0.2);
        nh_.param<double>(node_name_ + "/xkp", x_kp_, 1.0);
        nh_.param<double>(node_name_ + "/xkd", x_kd_, 0.0);
        nh_.param<double>(node_name_ + "/xki", x_ki_, 0.0);
        nh_.param<double>(node_name_ + "/ykp", y_kp_, 1.0);
        nh_.param<double>(node_name_ + "/ykd", y_kd_, 0.0);
        nh_.param<double>(node_name_ + "/yki", y_ki_, 0.0);

        algoX_ = new pidTrack::PidTrack(x_kp_, x_kd_, x_ki_);
        algoY_ = new pidTrack::PidTrack(y_kp_, y_kd_, y_ki_);

        rate_ = new ros::Rate(frequency_control_);

        move_pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local", 10);

        uavstate_sub_ = nh_.subscribe<mavros_msgs::State>("/mavros/state", 10, &uav::Uav::MsgUavState, this);
        dectpose_sub_ = nh_.subscribe<geometry_msgs::Vector3>("/reposition", 10, &uav::Uav::MsgDectPos, this);
        uavpose_sub_ = nh_.subscribe<geometry_msgs::PoseStamped>("/mavros/local_position/pose", 10, &uav::Uav::MsgUavPose, this);
        uavvel_sub_ = nh_.subscribe<geometry_msgs::TwistStamped>("/mavros/local_position/velocity", 10, &uav::Uav::MsgUavVel, this);
        mode_sub_ = nh_.subscribe<std_msgs::UInt16>("/gui_state", 1, &uav::Uav::MsgGuiState, this);
        arming_client = nh.serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
        set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
        //fun_re_ = std::bind(&uav::Uav::ParamDynamicReconfig,this,_1);
        server_.setCallback(boost::bind(&uav::Uav::ParamDynamicReconfig,this,_1));

        mode_track_ = uav::StateOnTrack::IDLE;
        mode_last_ =  uav::StateOnTrack::IDLE;
        //消息变量初始化
        ros::spinOnce();
        while (ros::ok() && !state_fcu_.connected)
        {
            ROS_INFO("PX4 not connect ,please wait!");
            usleep(500000);
            ros::spinOnce();
        }
        ROS_INFO("PX4 connected!");
        pose_ori_ = pose_;
        for (int i = 60; ros::ok() && i > 0; --i)
        {
            pose_target_ = pose_;
            pose_target_.pose.position.z=0.1;
            move_pub_.publish(pose_target_);
            ros::spinOnce();
            rate_->sleep();
        }

        offb_set_mode_.request.custom_mode = "OFFBOARD";
        arm_cmd_.request.value = true;

        ros::Time last_request = ros::Time::now();

        while (ros::ok() && (state_fcu_.mode != "OFFBOARD" || !state_fcu_.armed))
        {
            if (state_fcu_.mode != "OFFBOARD" &&
                (ros::Time::now() - last_request > ros::Duration(5.0)))
            {
                if (set_mode_client.call(offb_set_mode_) &&
                    offb_set_mode_.response.mode_sent)
                {
                    ROS_INFO("Offboard enabled!");
                }
                last_request = ros::Time::now();
            }
            else
            {
                if (!state_fcu_.armed &&
                    (ros::Time::now() - last_request > ros::Duration(5.0)))
                {
                    if (arming_client.call(arm_cmd_) &&
                        arm_cmd_.response.success)
                    {
                        ROS_INFO("Vehicle armed");
                    }
                    last_request = ros::Time::now();
                }
            }
            move_pub_.publish(pose_target_);
            ros::spinOnce();
            rate_->sleep();
        }

        ROS_INFO("uav start!");
    }

    Uav::~Uav()
    {
        algoX_->~PidTrack();
        algoY_->~PidTrack();
        delete rate_;
    }

    void Uav::RunTrack()
    {
        mode_track_ = uav::StateOnTrack::IDLE;
        while (ros::ok)
        {
            switch (mode_track_)
            {
            case uav::StateOnTrack::IDLE:
            {
                ROS_INFO("uav::StateOnTrack::IDLE");
                mode_last_ =  uav::StateOnTrack::IDLE;
                pose_target_ = pose_;
                pose_target_.header.stamp = ros::Time::now();
                pose_target_.header.frame_id = node_name_;
                break;
            }
            case uav::StateOnTrack::FLY:
            {
                ROS_INFO("uav::StateOnTrack::FLY");
                if(mode_last_  == uav::StateOnTrack::IDLE ){
                    pose_target_ = pose_;
                    pose_target_.pose.position.z = pose_ori_.pose.position.z + HEIGHT_TAKEOFF;
                    mode_last_ = uav::StateOnTrack::FLY;
                }

                if (abs(pose_.pose.position.z - (pose_ori_.pose.position.z + HEIGHT_TAKEOFF)) < 0.1)
                {
                    mode_track_ = uav::StateOnTrack::ONHEIGHT;
                    mode_last_ =  uav::StateOnTrack::ONHEIGHT;
                }
                pose_target_.header.stamp = ros::Time::now();
                pose_target_.header.frame_id = node_name_;
                break;
            }
            case uav::StateOnTrack::ONHEIGHT:
            {
                 mode_last_ =uav::StateOnTrack::ONHEIGHT;
                ROS_INFO("uav::StateOnTrack::ONHEIGHT");
                pose_target_ = pose_;
                pose_target_.pose.position.z = height_;
                pose_target_.header.stamp = ros::Time::now();
                pose_target_.header.frame_id = node_name_;
                break;
            }

            case uav::StateOnTrack::ONFIND:
            {
                pose_target_.pose.position.z = height_;
                mode_last_ =uav::StateOnTrack::ONFIND;
                ROS_INFO("uav::StateOnTrack::ONFIND");
                if (repose_dect_.x != 0 && repose_dect_.y != 0)
                {
                    //algoX_->setPosOri(repose_dect_.x);
                    //algoY_->setPosOri(repose_dect_.y);
                    algoX_->setPosOri(0);
                    algoY_->setPosOri(0);
                    mode_track_ = uav::StateOnTrack::ONTRACK;
                }
                pose_target_ = pose_;
                pose_target_.pose.position.z = height_;
                pose_target_.header.stamp = ros::Time::now();
                pose_target_.header.frame_id = node_name_;
                break;
            }
            case uav::StateOnTrack::ONTRACK:
            {
                pose_target_.pose.position.z = height_;
                mode_last_ = uav::StateOnTrack::ONTRACK;
                ROS_INFO("uav::StateOnTrack::ONTRACK");
                if (repose_dect_.x != 0 && repose_dect_.y != 0)
                {
                    lost_track_ = 0;
                    pose_target_.pose.position.x = pose_.pose.position.x + algoX_->runPosTrack(repose_dect_.x);
                    pose_target_.pose.position.y = pose_.pose.position.y + algoY_->runPosTrack(repose_dect_.y);
                    pose_target_.pose.position.z = height_;
                }
                else
                {
                    ROS_INFO("lost the mission %d", lost_track_);
                    ++lost_track_;
                    pose_target_ = pose_;
                    pose_target_.pose.position.z = height_;
                }
                if (lost_track_ > frequency_control_ * 20)
                {
                    mode_track_ = uav::StateOnTrack::LAND;
                }
                pose_target_.header.stamp = ros::Time::now();
                pose_target_.header.frame_id = node_name_;
                break;
            }
            case uav::StateOnTrack::LAND:
            {
                mode_last_ = uav::StateOnTrack::LAND;
                ROS_INFO("uav::StateOnTrack::LAND");
                pose_target_ = pose_;
                pose_target_.pose.position.z = pose_.pose.position.z - land_speed_ / frequency_control_;
                if (pose_.pose.position.z < HEIGHT_TAKEOFF && state_fcu_.mode != "AUTO.LAND")
                {
                    offb_set_mode_.request.custom_mode = "AUTO.LAND";
                    if (set_mode_client.call(offb_set_mode_) && offb_set_mode_.response.mode_sent)
                    {
                        ROS_INFO("uav is auto landing ");
                    }
                    else
                    {
                        pose_target_.pose.position.z = pose_.pose.position.z;
                    }
                }
                pose_target_.header.stamp = ros::Time::now();
                pose_target_.header.frame_id = node_name_;
                break;
            }
            case uav::StateOnTrack::XWARD:
            {
                ROS_INFO("uav::StateOnTrack::XWARD");
                if(mode_last_ !=uav::StateOnTrack::XWARD ){
                    pose_target_ = pose_;
                    pose_target_.pose.position.x = pose_.pose.position.x + 1.0;
                    pose_target_.pose.position.z = height_;
                    pose_target_.header.stamp = ros::Time::now();
                    pose_target_.header.frame_id = node_name_;
                    mode_last_ = uav::StateOnTrack::XWARD;
                }
                if(abs(pose_.pose.position.x-pose_target_.pose.position.x)<0.1){
                    mode_track_ = uav::StateOnTrack::ONHEIGHT;
                    mode_last_ = uav::StateOnTrack::ONHEIGHT;
                }
                break;
                
            }

            case uav::StateOnTrack::YWARD:
            {
                ROS_INFO("uav::StateOnTrack::YWARD");
                if(mode_last_!=uav::StateOnTrack::YWARD){
                    pose_target_ = pose_;
                    pose_target_.pose.position.y = pose_.pose.position.y + 1.0;
                    pose_target_.pose.position.z = height_;
                    pose_target_.header.stamp = ros::Time::now();
                    pose_target_.header.frame_id = node_name_;
                    mode_last_ = uav::StateOnTrack::YWARD;
                }
                
                if(abs(pose_.pose.position.y-pose_target_.pose.position.y)<0.1){
                    mode_track_ = uav::StateOnTrack::ONHEIGHT;
                    mode_last_ = uav::StateOnTrack::ONHEIGHT;
                }
                break;
            }

            case uav::StateOnTrack::XBACK:
            {

                ROS_INFO("uav::StateOnTrack::XBACK");
                if(mode_last_!=uav::StateOnTrack::XBACK){
                    pose_target_ = pose_;
                    pose_target_.pose.position.x = pose_.pose.position.x - 1.0;
                    pose_target_.pose.position.z = height_;
                    pose_target_.header.stamp = ros::Time::now();
                    pose_target_.header.frame_id = node_name_;
                    mode_last_ = uav::StateOnTrack::XBACK;
                }

                if(abs(pose_.pose.position.x-pose_target_.pose.position.x)<0.1){
                    mode_track_ = uav::StateOnTrack::ONHEIGHT;
                    mode_last_ = uav::StateOnTrack::ONHEIGHT;
                }
                break;
            }

            case uav::StateOnTrack::YBACK:
            {

                ROS_INFO("uav::StateOnTrack::YBACK");
                if(mode_last_!=uav::StateOnTrack::YBACK){
                    pose_target_ = pose_;
                    pose_target_.pose.position.y = pose_.pose.position.y - 1.0;
                    pose_target_.pose.position.z = height_;
                    pose_target_.header.stamp = ros::Time::now();
                    pose_target_.header.frame_id = node_name_;
                    mode_last_ = uav::StateOnTrack::YBACK;
                }
                if(abs(pose_.pose.position.y-pose_target_.pose.position.y)<0.1){
                    mode_track_ = uav::StateOnTrack::ONHEIGHT;
                    mode_last_ = uav::StateOnTrack::ONHEIGHT;
                }
                break;
            }

            // case uav::StateOnTrack::ROW:
            // {

            //     ROS_INFO("uav::StateOnTrack::ROW");
            //     if(mode_last_!=uav::StateOnTrack::ROW){
            //         pose_target_ = pose_;
            //         pose_target_.pose.position.y = pose_.pose.position.y - 1.0;
            //         pose_target_.pose.position.z = height_;
            //         pose_target_.header.stamp = ros::Time::now();
            //         pose_target_.header.frame_id = node_name_;
            //         mode_last_ = uav::StateOnTrack::YBACK;
            //     }
            //     if(abs(pose_.pose.position.y-pose_target_.pose.position.y)<0.1){
            //         mode_track_ = uav::StateOnTrack::ONHEIGHT;
            //         mode_last_ = uav::StateOnTrack::ONHEIGHT;
            //     }
            //     break;
            // }

            default:
            {
                mode_track_ = uav::StateOnTrack::LAND;
                mode_last_ =  uav::StateOnTrack::LAND;
                pose_target_ = pose_;
                pose_target_.header.stamp = ros::Time::now();
                pose_target_.header.frame_id = node_name_;
                break;
            }
            }
            
            move_pub_.publish(pose_target_);
            ros::spinOnce();
            rate_->sleep();
        }
    }

    void Uav::MsgUavState(const mavros_msgs::State::ConstPtr &statefromfcu)
    {
        state_fcu_ = *statefromfcu;
    }

    void Uav::MsgUavPose(const geometry_msgs::PoseStamped::ConstPtr &posefromfcu)
    {
        pose_ = *posefromfcu;
    }

    void Uav::MsgUavVel(const geometry_msgs::TwistStamped::ConstPtr &velfromfcu)
    {
        vel_ = *velfromfcu;
    }

    void Uav::MsgDectPos(const geometry_msgs::Vector3::ConstPtr &posefromdetect)
    {
        repose_dect_ = *posefromdetect;
    }
 
    void Uav::MsgGuiState(const std_msgs::UInt16::ConstPtr &msg)
    {
        mode_track_ = msg->data;
    }

    void Uav::ParamDynamicReconfig(track8yolo::param_pidConfig &config)
    {
        x_kp_ = config.xkp;
        x_kd_ = config.xkd;
        x_ki_ = config.xki;
        y_kp_ = config.ykp;
        y_kd_ = config.ykd;
        y_ki_ = config.yki;
    }
}