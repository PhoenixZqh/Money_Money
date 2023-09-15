
#include "detect_yolo.h"

namespace detect_yolo
{
    DetectYolo::DetectYolo(ros::NodeHandle &nh) : nh_(nh)
    {
        name_node_ = ros::this_node::getName();
        nh_.param<std::string>(name_node_ + "/engine_path", path_engine_, "/home/gdz/track_ws/src/track8yolo/weights/best.engine");
        nh.param<int>(name_node_ + "/widthnet", width_yolo_, 640);
        nh.param<int>(name_node_ + "/heightnet", height_yolo_, 640);
        nh_.param<int>(name_node_ + "fps", fps_, 30);

        distance3D_.x = 0; //位置
        distance3D_.y = 0; //位置
        distance3D_.z = 0; //位置

        bbox_pub_ = nh_.advertise<track8yolo::BoundingBox>("boundingbox", 100);   //发布检测框， x1, x2, y1, y2, label;
        distance_pub_ = nh_.advertise<geometry_msgs::Vector3>("reposition", 100); //发布跟踪位置;
        image_sub_ = nh_.subscribe<sensor_msgs::Image>("/airsim_node/PX4/front_center_custom/Scene",10,&detect_yolo::DetectYolo::MsgImageRGB,this);
        loop_rate_ = new ros::Rate(fps_);

        p.gpu_id = 0;
        p.net_height = height_yolo_;
        p.net_width = width_yolo_;
        p.confThreshold = 0.7; // 检测阈值  值越小越灵敏，越大误捡率越少
        p.nmsThreshold = 0.4;
        p.weightFile = (char *)(path_engine_.c_str());

        g_init = ALG_VIDEO_STOP;
        g_alg = new CYoloV5TensorRTClass(); //目标检测 & 轻量化———————————————————————
        g_init = g_alg->InitAlgoriParam(p); //初始化参数

        ROS_INFO("init down");
    }

    DetectYolo::~DetectYolo()
    {
        g_alg->~CYoloV5TensorRTClass();
        delete loop_rate_;
    }

    void DetectYolo::MsgImageRGB(const sensor_msgs::Image::ConstPtr &msg)
    {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        image_rgb_ = cv_ptr->image;
    }

    void DetectYolo::RunDetect()
    {
        ros::spinOnce();
        while (ros::ok())
        {
            distance3D_.x = 0;
            distance3D_.y = 0;
            distance3D_.z = 0;

            bboxResult_.xmin = 0;
            bboxResult_.ymin = 0;
            bboxResult_.xmax = 0;
            bboxResult_.ymax = 0;
            bboxResult_.label = 999;

            auto start = std::chrono::system_clock::now();
            std::vector<StruDetectInfo> vecFeed;
            g_alg->MainProcFunc(image_rgb_, vecFeed);
            auto end = std::chrono::system_clock::now();
            std::cout << "eclapse time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

            if (vecFeed.empty())
            {
                bboxResult_.xmin = 0;
                bboxResult_.ymin = 0;
                bboxResult_.xmax = 0;
                bboxResult_.ymax = 0;
                bboxResult_.label = 999;
            }

            float conf = 0;
            int idx = -1;
            for (long unsigned int i = 0; i < vecFeed.size(); i++)
            {
                if (vecFeed[i].label == 0 && vecFeed[i].confidance >= conf)
                {
                    conf = vecFeed[i].confidance;
                    idx = i;
                }
            }

            if (idx >= 0)
            {
                bboxResult_.xmin = vecFeed[idx].x;
                bboxResult_.ymin = vecFeed[idx].y;
                bboxResult_.xmax = vecFeed[idx].x + vecFeed[idx].width;
                bboxResult_.ymax = vecFeed[idx].y + vecFeed[idx].height;
                bboxResult_.label = vecFeed[idx].label;
                uint16_t width = image_rgb_.cols;
                uint16_t height = image_rgb_.rows;
                // distance3D_.x =(bboxResult_.xmin+bboxResult_.xmax-width)/2; //delta= box_center - img_center
                // distance3D_.y =(bboxResult_.ymin+bboxResult_.ymax-height)/2 ;

                // distance3D_.x =-(bboxResult_.xmin+bboxResult_.xmax-width)/2*1.8/320; //delta=-(box_center - img_center)
                // distance3D_.y =-(bboxResult_.ymin+bboxResult_.ymax-height)/2 *1.8/320; // img -> FLU 

                distance3D_.x =(bboxResult_.xmin+bboxResult_.xmax-width)/2; //delta=-(box_center - img_center)
                distance3D_.y =(bboxResult_.ymin+bboxResult_.ymax-height)/2; // img -> FLU

                // 画框
                cv::Rect r = cv::Rect(vecFeed[idx].x, vecFeed[idx].y, vecFeed[idx].width, vecFeed[idx].height);
		        cv::rectangle(image_rgb_, r, cv::Scalar(0, 255, 255), 2);
                
            }
            else
            {
                bboxResult_.xmin = 0;
                bboxResult_.ymin = 0;
                bboxResult_.xmax = 0;
                bboxResult_.ymax = 0;
                bboxResult_.label = 999;
                distance3D_.x = 0;
                distance3D_.y=0;
            }
            cv::imshow("src", image_rgb_);
            cv::waitKey(1);

            

            

            bbox_pub_.publish(bboxResult_);
            distance_pub_.publish(distance3D_);
            ros::spinOnce();


        }
    }

}