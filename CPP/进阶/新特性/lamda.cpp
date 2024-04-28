#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#define FUNDMENTAL

#ifdef FUNDMENTAL
/**
 * @brief  lambda表达式是一种匿名函数
 * 基本用法： [捕获列表](参数列表){}
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

#endif
