#include <iostream>
#include <chrono>
#include <string>

using namespace std;

template <typename Function>
double MeasureTime(Function func)
{
    auto start_time = std::chrono::high_resolution_clock::now();
    func(); // 执行传入的函数
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    return static_cast<double>(duration.count()); // 返回执行时间（毫秒）
}

void ForLoop(int i)
{
    for (int m = 0; m < 5000; m++)
    {
        for (int n = 0; n < 5000; n++)
        {
            i = i + m * n;
        }
    }
}

int Test1(int test)
{
    cout << test << endl;

    return test + 1;
}

int main()
{
    double time1 = MeasureTime([](int i = 10) { ForLoop(i); });
    double time2 = MeasureTime([](int tmp = 999) { int res = Test1(tmp); });

    cout << "执行时间1: " << time1 << "ms" << endl;

    return 0;
}