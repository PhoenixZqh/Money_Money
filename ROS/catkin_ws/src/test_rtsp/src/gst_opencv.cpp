#include <opencv2/opencv.hpp>

int main()
{
    // std::string pipe = "filesrc location=/home/zqh/test.mp4 ! qtdemux ! h264parse ! avdec_h264 ! videoconvert ! appsink";
    std::string pipe = "filesrc location=/home/zqh/test.mp4 ! qtdemux ! h264parse ! nvdec ! videoconvert ! appsink";

    cv::VideoCapture cap(pipe, cv::CAP_GSTREAMER);

    if (!cap.isOpened()) {
        std::cerr << "Error opening video file" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::imshow("Video", frame);
        if (cv::waitKey(30) == 27) { // Press 'Esc' key to exit
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}

// #include <opencv2/opencv.hpp>

// int main() {
//     std::string pipe = "filesrc location=path/to/your/video.mp4 ! qtdemux ! h264parse ! omxh264dec ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! appsink";

//     cv::VideoCapture cap(pipe, cv::CAP_GSTREAMER);

//     if (!cap.isOpened()) {
//         std::cerr << "Error opening video file" << std::endl;
//         return -1;
//     }

//     cv::Mat frame;
//     while (cap.read(frame)) {
//         cv::imshow("Video", frame);
//         if (cv::waitKey(30) == 27) {  // Press 'Esc' key to exit
//             break;
//         }
//     }

//     cap.release();
//     cv::destroyAllWindows();

//     return 0;
// }
