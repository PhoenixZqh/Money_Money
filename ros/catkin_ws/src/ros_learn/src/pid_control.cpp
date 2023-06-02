#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

using namespace std;
std::chrono::steady_clock::time_point last_time_ = std::chrono::steady_clock::now();

double calculateAngularVelocity(double currentAngle, double targetAngle, double kp, double ki, double kd)
{

    std::cout << "last_time_: " << std::chrono::duration_cast<std::chrono::microseconds>(last_time_.time_since_epoch()).count() << " microseconds since epoch" << std::endl;

    // 打印 current_time 的值
    auto current_time = std::chrono::steady_clock::now();

    std::cout << "current_time: " << std::chrono::duration_cast<std::chrono::microseconds>(current_time.time_since_epoch()).count() << " microseconds since epoch" << std::endl;

    auto delta_time = std::chrono::duration_cast<std::chrono::microseconds>(current_time - last_time_).count() / 1000.0;

    static double errorSum = 0.0;
    static double lastError = 0.0;

    double error = targetAngle - currentAngle;
    errorSum += error * delta_time;
    double errorRate = (error - lastError) / delta_time;
    lastError = error;
    last_time_ = current_time;

    double correction = kp * error + ki * errorSum + kd * errorRate;

    std::cout << "角速度：" << correction << " 度/秒" << std::endl;

    return correction;
}

int main()
{
    double currentAngle = 45.0;
    double targetAngle = 90.0;
    double kp = 0.1;
    double ki = 0.2;
    double kd = 0.1;

    while (true) {
        double angularVelocity = calculateAngularVelocity(currentAngle, targetAngle, kp, ki, kd);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}
