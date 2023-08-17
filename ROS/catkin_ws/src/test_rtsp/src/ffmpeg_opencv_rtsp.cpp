#include "opencv2/opencv_modules.hpp"
#include <iostream>
#if defined(HAVE_OPENCV_CUDACODEC)
#include <algorithm>
#include <condition_variable>
#include <cv_bridge/cv_bridge.h>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/core/opengl.hpp>
#include <opencv2/cudacodec.hpp>
#include <opencv2/highgui.hpp>
#include <queue>
#include <ros/ros.h>
#include <signal.h>
#include <string>
#include <thread>
#include <vector>

using namespace std;

FILE* ffmpeg_process;
mutex buffer_mutex;
queue<cv::Mat> image_buffer;
condition_variable image_available; // Condition variable to signal availability of new images

void FetchStream()
{
    const std::string fname = "/home/zqh/buck.mp4";
    cv::cuda::setDevice(0);

    cv::Mat frame;
    cv::cuda::GpuMat d_frame;

    cv::Ptr<cv::cudacodec::VideoReader> d_reader = cv::cudacodec::createVideoReader(fname);

    while (true) {

        if (!d_reader->nextFrame(d_frame))
            break;

        d_frame.download(frame);

        if (frame.empty()) {
            cerr << "End of video" << endl;
            break;
        }

        {
            lock_guard<mutex> lock(buffer_mutex);
            image_buffer.push(frame);
            image_available.notify_one(); // Signal availability of new image
        }

        usleep(5000);
    }
}

void sigintHandler(int sig)
{
    // Close ffmpeg process
    if (ffmpeg_process) {
        fclose(ffmpeg_process);
        ffmpeg_process = nullptr;
    }
    exit(0); // Terminate the program
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "nhy_camera");
    ros::NodeHandle nh;

    signal(SIGINT, sigintHandler);

    thread stream_thread(FetchStream);
    ffmpeg_process = popen("ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -framerate 30 -i - -c:v h264_nvenc -b:v 3000k -g 20 -preset fast -f rtsp rtsp://10.88.105.194:8554/nhy", "w");

    if (!ffmpeg_process) {
        cerr << "Failed to start ffmpeg process" << endl;
        return 1;
    }

    while (true) {
        cv::Mat frame;
        {
            unique_lock<mutex> lock(buffer_mutex);
            image_available.wait(lock, [] { return !image_buffer.empty(); }); // Wait for new image

            frame = image_buffer.front();
            image_buffer.pop();
        }

        if (!frame.empty()) {
            cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
            fwrite(frame.data, sizeof(uint8_t), frame.total() * frame.elemSize(), ffmpeg_process);
        }
    }

    fclose(ffmpeg_process);

    stream_thread.join();
    return 0;
}

#else

int main()
{
    std::cout << "OpenCV was built without CUDA Video decoding support\n"
              << std::endl;
    return 0;
}

#endif

// #include "opencv2/opencv_modules.hpp"
// #include <iostream>
// #if defined(HAVE_OPENCV_CUDACODEC)
// #include <algorithm>
// #include <cv_bridge/cv_bridge.h>
// #include <numeric>
// #include <opencv2/core.hpp>
// #include <opencv2/core/opengl.hpp>
// #include <opencv2/cudacodec.hpp>
// #include <opencv2/highgui.hpp>
// #include <queue>
// #include <ros/ros.h>
// #include <signal.h>
// #include <string>
// #include <thread>
// #include <vector>

// using namespace std;

// FILE* ffmpeg_process;
// mutex buffer_mutex;
// queue<cv::Mat> image_buffer;

// void FetchStream()
// {
//     const std::string fname = "/home/zqh/buck.mp4";
//     cv::cuda::setDevice(0);

//     cv::Mat frame;
//     cv::cuda::GpuMat d_frame;

//     cv::Ptr<cv::cudacodec::VideoReader> d_reader = cv::cudacodec::createVideoReader(fname);

//     static int index = 0;
//     while (true) {

//         index++;

//         if (!d_reader->nextFrame(d_frame))
//             break;

//         d_frame.download(frame);

//         // cout << frame.cols << "\t" << frame.rows << endl;

//         // string img_path = "/home/zqh/DATA/pic1/" + to_string(index) + ".jpg";
//         // cv::imwrite(img_path, frame);

//         // cv::imshow("GPU", frame);

//         // if (cv::waitKey(3) > 0)
//         //     break;

//         usleep(5000);

//         if (frame.empty()) {
//             cerr << "End of video" << endl;
//             break;
//         }

//         {
//             lock_guard<mutex> lock(buffer_mutex);
//             image_buffer.push(frame);
//         }
//     }
// }

// void sigintHandler(int sig)
// {
//     // Close ffmpeg process
//     if (ffmpeg_process) {
//         fclose(ffmpeg_process);
//         ffmpeg_process = nullptr;
//     }
//     exit(0); // Terminate the program
// }

// int main(int argc, char** argv)
// {
//     ros::init(argc, argv, "nhy_camera");
//     ros::NodeHandle nh;

//     signal(SIGINT, sigintHandler);

//     thread stream_thred(FetchStream);
//     ffmpeg_process = popen("ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -framerate 30 -i - -c:v h264_nvenc -b:v 3000k -g 20 -preset fast -f rtsp rtsp://10.88.105.194:8554/nhy", "w");

//     if (!ffmpeg_process) {
//         cerr << "Failed to start ffmpeg process" << endl;
//         return 1;
//     }

//     while (true) {
//         cv::Mat frame;
//         {
//             lock_guard<mutex> lock(buffer_mutex);
//             if (!image_buffer.empty()) {
//                 frame = image_buffer.front();
//                 image_buffer.pop();
//             }
//         }

//         if (!frame.empty()) {
//             cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
//             fwrite(frame.data, sizeof(uint8_t), frame.total() * frame.elemSize(), ffmpeg_process);
//         }
//     }

//     fclose(ffmpeg_process);

//     stream_thred.join();
//     return 0;
// }

// #else

// int main()
// {
//     std::cout << "OpenCV was built without CUDA Video decoding support\n"
//               << std::endl;
//     return 0;
// }

// #endif