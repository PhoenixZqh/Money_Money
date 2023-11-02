
#include <cv_bridge/cv_bridge.h>
#include <ros/ros.h>
#include <stdio.h>
#include <termio.h>

#include <iostream>
#include <memory>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;
int scanKeyboard() {
  int in;
  struct termios new_settings;
  struct termios stored_settings;
  tcgetattr(0, &stored_settings);
  new_settings = stored_settings;
  new_settings.c_lflag &= (~ICANON);
  new_settings.c_cc[VTIME] = 0;
  tcgetattr(0, &stored_settings);
  new_settings.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &new_settings);

  in = getchar();

  tcsetattr(0, TCSANOW, &stored_settings);
  return in;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "gimbal_camera");
  ros::NodeHandle nh;

  //   std::string pipline_str = "rtsp://192.168.42.10/livestream/12";
  std::string pipline_str = "/home/zqh/2.mp4";

  cv::VideoCapture cap(pipline_str);

  if (!cap.isOpened()) {
    std::cout << "CAN NOT OPEN CAMERA" << std::endl;
  }

  int index = 0;
  cv::Mat frame;

  while (ros::ok()) {
    cap >> frame;

    if (frame.empty()) {
      std::cout << "img empty!!" << std::endl;
      // break;
      continue;
    }

    // int ascii = scanKeyboard();
    cv::imshow("sss", frame);
    char key_value = cv::waitKey(50);

    if (key_value == 's') {
      index++;
      string img_name = "/home/zqh/pic/" + to_string(index) + ".png";

      imwrite(img_name, frame);
      cout << "成功保存一张:" << index << endl;
    }

    // else if (ascii == 27) { // ESC
    //   break;
    // }
  }

  return 0;
}

// int main()
// {
//     while (1) {

//         int ascii = scanKeyboard();

//         cout << ": " << ascii << "\t";

//         if (ascii == 115) {
//             cout << "yes" << endl;
//         }

//         else if (ascii == 27) {
//             break;
//         }
//     }
// }
