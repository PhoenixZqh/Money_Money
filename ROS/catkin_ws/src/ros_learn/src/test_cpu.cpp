#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <cmath>
#include <atomic>

// 定义计算密集型任务
void cpuIntensiveTask(std::atomic<bool> &running)
{
    while (running.load())
    {
        volatile double result = 0.0;
        for (int i = 0; i < 100000000000000000; ++i)
        {
            result += std::sin(i) * std::cos(i);
        }
    }
}

int main()
{
    // 获取系统中的硬件线程数
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0)
    {
        numThreads = 2; // 默认至少使用2个线程
    }
    std::cout << "Running on " << numThreads << " threads." << std::endl;

    // 创建一个标志来控制任务运行
    std::atomic<bool> running(true);

    // 创建线程并启动任务
    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back(cpuIntensiveTask, std::ref(running));
    }

    // 运行一段时间（例如10秒）
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // 停止任务
    running.store(false);

    // 等待所有线程完成
    for (auto &t : threads)
    {
        t.join();
    }

    std::cout << "Finished running CPU intensive tasks." << std::endl;
    return 0;
}
