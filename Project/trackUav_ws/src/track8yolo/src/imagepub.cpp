#include<ros/ros.h>
#include"detect_yolo.h"

int main(int argc ,char * argv[]){
    ros::init(argc,argv,"img_publisher");
    ros::NodeHandle nh;
    detect_yolo::DetectYolo   *yolopub = new detect_yolo::DetectYolo(nh);
    yolopub->RunDetect();
    ros::spin();
    yolopub->~DetectYolo();
    return EXIT_SUCCESS;

}