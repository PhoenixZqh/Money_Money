#include <iostream>
#include <netinet/in.h>
#include <opencv2/opencv.hpp>
#include <sys/socket.h>
#include <unistd.h>

/**
 * @brief udp 接收图片
*/

#define HOST "127.0.0.1"
#define PORT 9999
#define BUFF_SIZE 65535

int main()
{
    int serverSocket;
    struct sockaddr_in serverAddress;

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed");
        return -1;
    }

    // Server address configuration
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Binding failed");
        close(serverSocket);
        return -1;
    }

    std::cout << "Now waiting for frames..." << std::endl;

    cv::Mat frame;

    while (true)
    {
        // Receive the length of encoded frame
        int length;
        if (recv(serverSocket, &length, sizeof(length), 0) < 0)
        {
            perror("Failed to receive frame size");
            break;
        }

        // Check for close message
        if (length == 1)
        {
            break;
        }

        // Receive the encoded frame data in chunks
        std::vector<uint8_t> buffer;
        size_t totalReceived = 0;
        while (totalReceived < length)
        {
            size_t remaining = length - totalReceived;
            size_t toReceive = std::min(remaining, static_cast<size_t>(BUFF_SIZE));
            std::vector<uint8_t> chunk(toReceive);
            ssize_t received = recv(serverSocket, chunk.data(), toReceive, 0);
            if (received < 0)
            {
                perror("Failed to receive frame data");
                close(serverSocket);
                return -1;
            }
            totalReceived += received;
            buffer.insert(buffer.end(), chunk.begin(), chunk.begin() + received);
        }

        // Decode the frame
        frame = cv::imdecode(buffer, cv::IMREAD_COLOR);
        if (frame.empty())
        {
            std::cout << "Invalid frame" << std::endl;
            continue;
        }

        cv::resize(frame, frame, cv::Size(640, 480));

        std::cout << "Received one frame" << std::endl;

        // Display the frame
        cv::imshow("Frames", frame);

        // Check for ESC key press to exit
        cv::waitKey(1);
    }

    // Release resources
    close(serverSocket);
    cv::destroyAllWindows();

    return 0;
}
