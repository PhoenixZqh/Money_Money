/*
 * @Author: Phoenix_Z
 * @Date: 2022-11-09 11:30:26
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-11-09 11:30:26
 * @Description:
 */

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

class Person {
private:
    int m_age;
    float m_score;

public:
    static int m_i; //静态成员变量

    static int add(int a, int b)
    {
        return a + b;
    }

    Person(int a, int b)
        : m_age(a)
        , m_score(b)
    {
        cout << "im constructor" << endl;
    }

    Person() = default;

    ~Person()
    {
        cout << "im destructor" << endl;
    }

    void show(int a, int b, int (*funcptr)(int, int))
    {
        cout << (*funcptr)(a, b) << endl;
    }

    void show1(int a, int b, function<int(int, int)> f1)
    {
        cout << f1(a, b) << endl;
    }
};

void TestStatic()
{
    int a = 0;
    static int b = 0;
    cout << "a++: " << a++
         << "\t"
         << "b++: " << b++
         << endl;
}

int main()
{

    Person p;
    auto funcPtr = &Person::add; //设置add函数的指针
    p.show(22, 22, funcPtr);

    auto f1 = bind(&Person::add, _1, _2); //使用bind绑定器
    p.show1(2, 3, f1);

    int n = 5;
    int j = 76;
    while (n--) {
        TestStatic();
    }

    if (1) {
        static Person p1(1, 1.2); //加了static ，作用阈在全局，而不在if循环内，所以先end然后析构
    }

    auto f2 = [&j](int a) {
        return j + a;
    };

    cout << "test lambda: " << f2(9) << endl;

    cout << "end!" << endl;

    return 0;
}