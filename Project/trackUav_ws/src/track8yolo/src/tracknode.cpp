#include<ros/ros.h>
#include"uav_track.h"

int main(int argc ,char * argv[]){
    ros::init(argc,argv,"jar_track");
    ros::NodeHandle nh;
    uav::Uav *p450 = new uav::Uav(nh);
    p450->RunTrack();
    ros::spin();
    p450->~Uav();
    return EXIT_SUCCESS;

}