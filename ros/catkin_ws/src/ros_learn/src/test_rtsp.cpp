#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <queue>
#include <signal.h>
#include <stdio.h>
#include <thread>
#include <unistd.h>

using namespace std;

FILE* ffmpeg_process;
mutex buffer_mutex;
queue<vector<uint8_t>> image_buffer;

void readImageFrames(const string& filename)
{
    cv::VideoCapture cap(filename);
    if (!cap.isOpened()) {
        cerr << "Failed to open video file: " << filename << endl;
        return;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::imshow("GPU", frame);

        if (cv::waitKey(3) > 0)
            break;
        vector<uint8_t> image_data(frame.data, frame.data + frame.total() * frame.elemSize());

        lock_guard<mutex> lock(buffer_mutex);
        image_buffer.push(image_data);
    }
}

void processImageBuffer()
{
    while (true) {
        if (!image_buffer.empty()) {
            lock_guard<mutex> lock(buffer_mutex);

            if (!image_buffer.empty()) {
                const vector<uint8_t>& image_data = image_buffer.front();

                fwrite(image_data.data(), sizeof(uint8_t), image_data.size(), ffmpeg_process);

                image_buffer.pop();
            }
        }

        usleep(1000); // Sleep for a short while to avoid busy waiting
    }
}

void sigintHandler(int sig)
{
    if (ffmpeg_process) {
        fclose(ffmpeg_process);
        ffmpeg_process = nullptr;
    }
    exit(0);
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_video_file>" << endl;
        return 1;
    }

    // Open input video file and start reading image frames
    string inputFilename = argv[1];
    thread read_thread(readImageFrames, inputFilename);

    // Start FFmpeg process for RTSP streaming
    string ffmpeg_command = "ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -framerate 30 -i - -c:v h264_nvenc -b:v 3000k -g 30 -preset fast -f rtsp rtsp://10.88.105.194:8554/nhy";
    ffmpeg_process = popen(ffmpeg_command.c_str(), "w");
    if (!ffmpeg_process) {
        cerr << "Failed to start FFmpeg process" << endl;
        return 1;
    }
    signal(SIGINT, sigintHandler);

    // Start image processing thread
    thread process_thread(processImageBuffer);

    // Wait for threads to finish
    read_thread.join();
    process_thread.join();

    return 0;
}

// #include <fstream>
// #include <iostream>
// #include <mutex>
// #include <opencv2/opencv.hpp>
// #include <queue>
// #include <ros/ros.h>
// #include <sensor_msgs/Image.h>
// #include <signal.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <thread> // Add this line to include the <thread> header
// #include <unistd.h>

// using namespace std;

// ros::Subscriber image_sub;
// FILE* ffmpeg_process;
// mutex buffer_mutex;
// queue<vector<uint8_t>> image_buffer;

// void imageCallback(const sensor_msgs::Image::ConstPtr& msg)
// {
//     // cout << "收到图像" << endl;

//     try {
//         // 获取图像数据
//         const std::vector<uint8_t>& image_data = msg->data;

//         // 将图像数据放入缓冲区
//         lock_guard<mutex> lock(buffer_mutex);
//         image_buffer.push(image_data);

//     } catch (const std::exception& e) {
//         ROS_ERROR("处理图像数据时出错：%s", e.what());
//     }
// }

// void processImageBuffer()
// {

//     while (ros::ok()) {
//         ros::spinOnce();
//         ros::Duration(0.01).sleep();

//         double start_time = cv::getTickCount();
//         // 等待获取锁
//         lock_guard<mutex> lock(buffer_mutex);

//         // 检查是否有图像数据
//         if (image_buffer.empty()) {
//             continue;
//         }

//         // 获取图像数据
//         const std::vector<uint8_t>& image_data = image_buffer.front();

//         // 将图像数据传递给 ffmpeg 的标准输入
//         fwrite(image_data.data(), sizeof(uint8_t), image_data.size(), ffmpeg_process);

//         double end_time = cv::getTickCount();
//         // double elapsed_time_ms = (end_time - start_time) / cv::getTickFrequency() * 1000;
//         // std::cout << "执行时间：" << elapsed_time_ms << " 毫秒" << std::endl;

//         // 弹出已处理的图像数据
//         image_buffer.pop();
//     }
// }

// void sigintHandler(int sig)
// {
//     // 关闭 ffmpeg 进程
//     if (ffmpeg_process) {
//         fclose(ffmpeg_process);
//         ffmpeg_process = nullptr;
//     }
//     ros::shutdown();
// }

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "image_to_ffmpeg");

//     // 初始化 ROS 节点
//     ros::NodeHandle nh;

//     // 订阅 ROS 图像话题（根据实际话题名称进行订阅）
//     image_sub = nh.subscribe("/nhy/gimbal_camera", 10, imageCallback);
//     // image_sub = nh.subscribe("/image_track_box", 10, imageCallback);

//     // 启动 ffmpeg 进程并将其标准输入重定向到管道

//     ffmpeg_process = popen("ffmpeg -f rawvideo -pixel_format bgr24 -video_size 1280x720 -framerate 30 -i - -c:v h264_nvenc -b:v 1000k -g 10 -preset fast -f rtsp rtsp://10.88.105.194:8554/nhy", "w");

//     if (!ffmpeg_process) {
//         ROS_ERROR("无法启动 ffmpeg 进程");
//         return 1;
//     }

//     // 设置 SIGINT 信号处理程序，以便在收到 Ctrl+C 时关闭 ffmpeg 进程
//     signal(SIGINT, sigintHandler);

//     // 启动图像数据处理线程
//     thread process_thread(processImageBuffer);

//     // 等待线程结束
//     process_thread.join();
//     ros::spin();

//     return 0;
// }
