/*
 - Author: phoenixZ
 - Date: 2024-04-28 09:41:13
 - Description: 
 *  lambda表达式是一种匿名函数
 *  基本用法： [捕获列表](参数列表){}
*/

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#define NONE

#ifdef FUNDMENTAL
/**
 * @brief  基本用法示例
*/

using namespace std;

class Person
{
private:
    int m_age;
    float m_score;

public:
    Person(int age, float score)
        : m_age(age), m_score(score)
    {
    }

    void test()
    {
        auto f1 = [this]() {
            cout << "test: " << m_age << endl;
        };
        f1();
    }
};

int main()
{
    int a = 111;
    int b = -1;
    auto f1 = [=](int c) mutable {
        a += 9;
        return a + c;
    };

    auto f2 = [&]() mutable {
        b += 1;
    };

    f2();
    cout << "a的值: " << a << endl;
    cout << "b的值: " << b << endl;
    cout << f1(3) << endl;

    Person p(100, 122);
    p.test();
    return 0;
}

#elif defined(ASARGS)

/**
 * @brief  lamda 表达式作函数参数
*/

int Func1(int &a, int &b, std::function<int(int, int)> func)
{
    auto res = func(a, b);
    std::cout << "res: " << res << std::endl;
    return res;
}

int main()
{
    int a = 20, b = 200;

    Func1(a, b, [&](int c, int d) { return c + d; });

    return 0;
}

#else

/**
 * @brief lamda 表达式和STL的结合
*/

int main()
{
    std::vector<int> arr = {3, 2, 21, 454, 213, 53, 6, 343, 2131, 654, 2323, 11, 0};
    std::sort(arr.begin(), arr.end(), [](int a, int b) { return a > b; });

    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << " " << std::endl;
    }

    return 0;
}

#endif
