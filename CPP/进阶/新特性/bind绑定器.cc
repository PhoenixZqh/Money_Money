/*
 * 可以调用对象包括:
    1. 函数指针
    2. 仿函数
    3. 类成员函数
    4. 可被转换成函数指针的类对象
 * function说明：
    1. 是一个类模板，可以容纳上述可调用对象
    2. 指定模板参数， 它可以采用统一的方式处理可调用对象，并允许保存和延迟使用他们
 * bind说明：
    1. 将可调用对象与其参数绑定在一起
    2. 绑定后的结果可以通过function保存
    3. placehoders 占位置符
*/

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

#define FUNCTION

#ifdef BIND

/**
 * @brief bind绑定器使用示例
*/

void Test(int a)
{
    cout << __func__ << "->" << a << endl;
}

class Person
{
private:
public:
    int m_a;
    Person() = default;
    Person(int a)
        : m_a(a)
    {
    }

    int operator()(int b)
    {
        return m_a + b;
    }

    void show(int a)
    {
        cout << __func__ << "->" << a << endl;
    }
};

int main()
{
    Person p1;

    //绑定普通函数
    auto f1 = bind(Test, _1);
    f1(11);

    //绑定成员函数
    auto f2 = bind(&Person::show, &p1, 2);
    f2(2);

    //绑定成员变量（public）
    auto f3 = bind(&Person::m_a, &p1);
    f3() = 111;
    cout << p1.m_a << endl;

    return 0;
}

#elif defined(FUNCTION)

/**
 * @brief function 使用示例
*/

int Add(int a, int b)
{
    return a + b;
}

void show(int a, int b, function<int(int, int)> f1)
{
    cout << __func__ << "->" << f1(a, b) << endl;
}

void Test(int a)
{
    cout << __func__ << "->" << a << endl;
}

int main()
{
    function<void(int)> f1 = bind(Test, _1);
    f1(2);

    auto f2 = bind(Test, 3);
    f2();

    auto f3 = bind(Add, _1, _2);

    show(1, 2, f3);    // function作为参数
    show(10, 20, Add); // 传递函数指针

    return 0;
}

#endif