// #include <functional>
// #include <iostream>
// #include <memory>
// #include <string>
// #include <vector>

// using namespace std;
// using namespace std::placeholders;

// void Test(int a)
// {
//     cout << __func__ << "->" << a << endl;
// }

// class Person {
// private:
// public:
//     int m_a;
//     Person() = default;
//     Person(int a)
//         : m_a(a)
//     {
//     }

//     int operator()(int b)
//     {

//         return m_a + b;
//     }

//     void show(int a)
//     {
//         cout << __func__ << "->" << a << endl;
//     }
// };

// int main()
// {
//     Person p1;

//     //绑定普通函数
//     auto f1 = bind(Test, _1);
//     f1(11);

//     //绑定成员函数
//     auto f2 = bind(&Person::show, &p1, 2);
//     f2(2);

//     //绑定成员变量（public）
//     auto f3 = bind(&Person::m_a, &p1);
//     f3() = 111;
//     cout << p1.m_a << endl;

//     return 0;
// }

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

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

    show(1, 2, f3); // function作为参数

    return 0;
}