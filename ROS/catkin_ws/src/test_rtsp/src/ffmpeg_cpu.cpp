#include <condition_variable> // Add this line to include the condition_variable header
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <signal.h>
#include <stdio.h>
#include <thread>
#include <unistd.h>

using namespace std;

FILE* ffmpeg_process;
mutex buffer_mutex;
condition_variable image_available; // Condition variable to signal availability of new images
queue<cv::Mat> image_buffer;

void processImageBuffer()
{
    cv::VideoCapture cap("/home/zqh/buck.mp4"); // Replace with your video file path

    if (!cap.isOpened()) {
        cerr << "Error opening video file" << endl;
        return;
    }

    while (true) {
        cv::Mat frame;
        cap >> frame;

        if (frame.empty()) {
            cerr << "End of video" << endl;
            break;
        }

        {
            lock_guard<mutex> lock(buffer_mutex);
            image_buffer.push(frame.clone()); // Clone the frame before pushing
            image_available.notify_one(); // Notify waiting thread that a new image is available
        }

        usleep(5000); // Sleep for 10 ms
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
    signal(SIGINT, sigintHandler);

    // Start the image processing thread
    thread process_thread(processImageBuffer);

    // Start ffmpeg process and redirect its input
    ffmpeg_process = popen("ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -framerate 30 -i - -c:v h264_nvenc -b:v 3000k -g 20 -preset fast -f rtsp rtsp://10.88.105.194:8554/nhy", "w");

    if (!ffmpeg_process) {
        cerr << "Failed to start ffmpeg process" << endl;
        return 1;
    }

    while (true) {
        cv::Mat frame;
        {
            unique_lock<mutex> lock(buffer_mutex);
            // Wait for a new image to be available or exit if the process is shutting down
            image_available.wait(lock, [&]() { return !image_buffer.empty(); });
            frame = image_buffer.front();
            image_buffer.pop();
        }

        if (!frame.empty()) {
            fwrite(frame.data, sizeof(uint8_t), frame.total() * frame.elemSize(), ffmpeg_process);
        }
    }

    fclose(ffmpeg_process);
    process_thread.join();

    return 0;
}

// #include <iostream>
// #include <opencv2/opencv.hpp>
// #include <signal.h>
// #include <stdio.h>
// #include <thread>
// #include <unistd.h>

// using namespace std;

// FILE* ffmpeg_process;
// mutex buffer_mutex;
// queue<cv::Mat> image_buffer;

// void processImageBuffer()
// {
//     cv::VideoCapture cap("/home/zqh/buck.mp4"); // Replace with your video file path

//     if (!cap.isOpened()) {
//         cerr << "Error opening video file" << endl;
//         return;
//     }

//     while (true) {
//         cv::Mat frame;
//         cap >> frame;

//         if (frame.empty()) {
//             cerr << "End of video" << endl;
//             break;
//         }

//         usleep(1000); // Sleep for 10 ms

//         {
//             lock_guard<mutex> lock(buffer_mutex);
//             image_buffer.push(frame.clone()); // Clone the frame before pushing
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
//     signal(SIGINT, sigintHandler);

//     // Start the image processing thread
//     thread process_thread(processImageBuffer);

//     // Start ffmpeg process and redirect its input
//     ffmpeg_process = popen("ffmpeg -f rawvideo -pixel_format bgr24 -video_size 320x240 -framerate 30 -i - -c:v h264_nvenc -b:v 1000k -g 10 -preset fast -f rtsp rtsp://10.88.105.194:8554/nhy", "w");

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
//             fwrite(frame.data, sizeof(uint8_t), frame.total() * frame.elemSize(), ffmpeg_process);
//         }
//     }

//     fclose(ffmpeg_process);
//     process_thread.join();

//     return 0;
// }
