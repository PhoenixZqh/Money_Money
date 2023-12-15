#include <arpa/inet.h>
#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <netinet/in.h>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>
#include <sensor_msgs/CompressedImage.h>
#include <sensor_msgs/Image.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * @brief UDP 发送图片
*/

#define HOST "127.0.0.1"
#define PORT 9999
#define CHUNK_SIZE 4096

void imageCallback(const sensor_msgs::ImageConstPtr &msg)
{
    cv_bridge::CvImagePtr cvImagePtr;
    try
    {
        // Convert ROS image message to OpenCV image
        cvImagePtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    // Get the OpenCV image
    cv::Mat frame = cvImagePtr->image;

    // std::vector<uchar> buffer;
    std::vector<uint8_t> buffer;
    std::vector<int> encodeParams;
    encodeParams.push_back(cv::IMWRITE_JPEG_QUALITY);
    encodeParams.push_back(55); // 设置较高的压缩质量，例如90

    cv::imencode(".jpg", frame, buffer, encodeParams);

    // cv::imencode(".jpg", frame, buffer, std::vector<int>({ cv::IMWRITE_JPEG_QUALITY, 1 }));

    // Create socket
    int serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        return;
    }

    // Server address configuration
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    if (inet_pton(AF_INET, HOST, &serverAddress.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        close(serverSocket);
        return;
    }

    // Connect to server
    if (connect(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Connection failed");
        close(serverSocket);
        return;
    }

    // Send the length of encoded frame
    int frameSize = buffer.size();
    if (send(serverSocket, &frameSize, sizeof(frameSize), 0) < 0)
    {
        perror("Failed to send frame size");
        close(serverSocket);
        return;
    }

    // Send the encoded frame data in chunks
    size_t totalSent = 0;
    while (totalSent < buffer.size())
    {
        size_t remaining = buffer.size() - totalSent;
        size_t toSend = std::min(remaining, static_cast<size_t>(CHUNK_SIZE));
        if (send(serverSocket, buffer.data() + totalSent, toSend, 0) < 0)
        {
            perror("Failed to send frame data");
            close(serverSocket);
            return;
        }
        totalSent += toSend;
    }

    std::cout << "Sent one frame" << std::endl;

    // Release resources
    close(serverSocket);
}

int main(int argc, char **argv)
{
    // Initialize ROS node
    ros::init(argc, argv, "image_sender");
    ros::NodeHandle nh;

    // Subscribe to the image topic
    ros::Subscriber sub = nh.subscribe("/nhy/gimbal_camera", 1, imageCallback);

    ros::spin();

    return 0;
}
