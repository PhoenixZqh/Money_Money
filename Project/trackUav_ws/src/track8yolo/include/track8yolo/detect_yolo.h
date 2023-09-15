#ifndef _DETECT_YOLO_H_
#define _DETECT_YOLO_h

#include <ros/ros.h>
#include<iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/Int32MultiArray.h>
#include <geometry_msgs/Vector3.h>
#include <pthread.h>
#include <chrono>

#include <track8yolo/BoundingBox.h>
#include "BaseYoloTensorRTDll.h"

namespace detect_yolo
{
    class DetectYolo : public ros::NodeHandle
    {
    public:
        explicit DetectYolo(ros::NodeHandle &nh);
        ~DetectYolo();
        DetectYolo(const DetectYolo &) = delete;
        DetectYolo operator=(const DetectYolo &) = delete;
        void RunDetect();

    private:
        void MsgImageRGB(const sensor_msgs::Image::ConstPtr &msg);

        ros::NodeHandle nh_;
        std::string name_node_;
        int fps_;
        geometry_msgs::Vector3 distance3D_;
        std::string path_engine_;

        cv::Mat image_rgb_;
        //cv::Mat image_depth_;

        // image_transport::ImageTransport it;
        //image_transport::Publisher pub;
        ros::Publisher bbox_pub_;
        ros::Publisher distance_pub_;
        ros::Subscriber image_sub_;
        // ros::Subscriber depth_sub;

        ros::Rate *loop_rate_;
        track8yolo::BoundingBox bboxResult_; //检测框


        int width_yolo_;
        int height_yolo_;
        int g_init;
        CYoloV5TensorRTClass *g_alg = nullptr;

        StruInitParams p;
    };
}

#endif
