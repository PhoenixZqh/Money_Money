/*
 - Author: phoenixZ
 - Date: 2024-07-08 09:34:12
 - Description: 测试自带swap，自实现swap， 移动语义实现的swap的耗时
*/

#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>

class Timer
{
public:
    Timer()
        : start_time_point(std::chrono::high_resolution_clock::now())
    {}

    void reset()
    {
        start_time_point = std::chrono::high_resolution_clock::now();
    }

    double elapsedMilliseconds() const
    {
        auto end_time_point = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end_time_point - start_time_point).count();
    }

    double elapsedSeconds() const
    {
        auto end_time_point = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double>(end_time_point - start_time_point).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
};

void Test1(int &l, int &r)
{
    std::swap(l, r);
}

void Test2(int &l, int &r)
{
    auto tmp = l;
    l = r;
    r = tmp;
}

void Test3(int &l, int &r)
{
    auto tmp(std::move(l));
    l = std::move(r);
    r = std::move(tmp);
}

void Test4(std::vector<int> &a, std::vector<int> &b)
{
    auto tmp = a;
    a = b;
    b = tmp;
}

/**
 * @brief 对于复杂类型的，移动语义可以避免资源分配和释放， 有效提升代码效率
*/
void Test5(std::vector<int> &a, std::vector<int> &b)
{
    auto tmp(std::move(a));
    a = std::move(b);
    b = std::move(tmp);
}

int main()
{
    int a = 10, b = 20;

    const size_t arr_size = 1000000;
    std::vector<int> arr1(arr_size, 1);
    std::vector<int> arr2(arr_size, 2);

    std::cout << "----------------------TEST1----------------------- " << std::endl;
    Timer t1;
    Test1(a, b);
    std::cout << "耗时: " << t1.elapsedMilliseconds() << " 毫秒" << std::endl;
    std::cout << "test1交换后: " << a << " , " << b << "\n"
              << std::endl;

    std::cout << "----------------------TEST2----------------------- " << std::endl;
    t1.reset();
    Test2(a, b);
    std::cout << "耗时: " << t1.elapsedMilliseconds() << " 毫秒" << std::endl;
    std::cout << "test2交换后: " << a << " , " << b << "\n"
              << std::endl;

    std::cout << "----------------------TEST3----------------------- " << std::endl;
    t1.reset();
    Test3(a, b);
    std::cout << "耗时: " << t1.elapsedMilliseconds() << " 毫秒" << std::endl;
    std::cout << "test3交换后: " << a << " , " << b << "\n"
              << std::endl;

    std::cout << "----------------------TEST4----------------------- " << std::endl;
    t1.reset();
    Test4(arr1, arr2);
    std::cout << "耗时: " << t1.elapsedMilliseconds() << " 毫秒" << std::endl;
    std::cout << "test4交换后: " << arr1[0] << " , " << arr2[0] << "\n"
              << std::endl;

    std::cout << "----------------------TEST5----------------------- " << std::endl;
    t1.reset();
    Test5(arr1, arr2);
    std::cout << "耗时: " << t1.elapsedMilliseconds() << " 毫秒" << std::endl;
    std::cout << "test5交换后: " << arr1[0] << " , " << arr2[0] << "\n"
              << std::endl;

    return 0;
}
