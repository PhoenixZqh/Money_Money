
#include "MySocketServer.h"
#include "Mqtt_Client.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "websocket_video_package_node");
    ros::NodeHandle nh("~");
    int websocketport;
    std::string topicName_rgb;
    nh.param<int>("websocketport", websocketport, 9002);
    nh.param<std::string>("topicName_rgb", topicName_rgb, "");
    MySocketServer ws_server(websocketport);

//    MySocketServer ws_server(9636);
//    std::string address = "tcp://10.88.105.20:1883";
//    std::string clientid = "drone_video";
//    std::string topicName_rgb =  "/camera/color/image_raw/compressed";
    
    Mqtt_Client mqttClient(nh, ws_server, topicName_rgb);

    std::thread ros_thread([&]() {
        ros::spin();
    });
    ws_server.run();
    ros_thread.join();
    return 0;
}

