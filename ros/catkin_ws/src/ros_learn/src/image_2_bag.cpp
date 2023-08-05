#include <cv_bridge/cv_bridge.h>
#include <dirent.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ros/console.h>
#include <rosbag/bag.h>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
using namespace std;
using namespace cv;

void GetFileNames(string path, vector<string>& filenames, string con);
void GetFileNamesByGlob(cv::String path, vector<cv::String>& filenames, string con);
int main(int argc, char** argv)
{
    // 输入文件和输出文件路径
    string base_dir = "/home/zqh/DATA/sequences/";
    string img_dir = base_dir + "uav0000077_00720_v/";
    string output_bag = base_dir + "less.bag";
    string img_format = ".jpg"; // 格式
    vector<string> img_names;
    GetFileNames(img_dir, img_names, ".jpg");
    cout << "img_names.size: " << img_names.size() << endl;
    cout << "图片读取完成" << endl;

    cout << "----" << endl;

    ros::Time::init();
    rosbag::Bag bag;
    bag.open(output_bag, rosbag::bagmode::Write);
    int seq = 0;
    vector<string>::iterator it;
    for (it = img_names.begin(); it != img_names.end(); it++) // todo 之后改成图片数量的多少
    {
        string tmp = *it;
        // cout<<tmp<<endl;
        string strImgFile = img_dir + tmp + img_format;
        usleep(100000); // 4hz
        ros::Time timestamp_ros = ros::Time::now();

        // --- for image ---//
        cv::Mat img = cv::imread(strImgFile);
        if (img.empty())
            cout << "图片为空: " << strImgFile << endl;
        cv_bridge::CvImage ros_image;
        sensor_msgs::ImagePtr ros_image_msg;

        ros_image.image = img;
        ros_image.encoding = "bgr8";
        // cout<<"debug_______"<<endl;
        // ros::Time timestamp_ros2 = ros::Time::now();
        ros_image_msg = ros_image.toImageMsg();
        ros_image_msg->header.seq = seq;
        ros_image_msg->header.stamp = timestamp_ros;
        ros_image_msg->header.frame_id = "/image_raw";

        bag.write("/cam", ros_image_msg->header.stamp, ros_image_msg);
        cout << "write frame: " << seq << endl;
        seq++;
    }

    cout << "---end---" << endl;

    return 0;
}

// con:文件格式 form:文件命名形式
void GetFileNames(string path, vector<string>& filenames, string con)
{
    DIR* pDir;
    struct dirent* ptr;
    string filename, format, name, name2;

    if (!(pDir = opendir(path.c_str())))
        return;
    int num = 0;
    while ((ptr = readdir(pDir)) != 0) {
        // 跳过.和..文件
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        filename = ptr->d_name;
        format = filename.substr(filename.find("."), filename.length());
        // name = filename.substr(0, filename.find("."));
        name = filename.substr(0, filename.find("."));
        cout << filename << "\t" << name << "\t" << format << endl;

        if (format == con) // 也可以添加对文件名的要求
        {
            filenames.push_back(name);

            num++;
        }
    }
    std::cout << "file size of:" << filenames.size() << "****" << num << std::endl;
    closedir(pDir);
}
