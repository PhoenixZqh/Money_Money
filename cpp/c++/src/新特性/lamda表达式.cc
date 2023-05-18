// /*
//  * @Author: Phoenix_Z
//  * @Date: 2022-10-12 09:30:52
//  * @Last Modified by: Phoenix_Z
//  * @Last Modified time: 2022-10-12 09:30:52
//  * @Description:
//  */

// #include <functional>
// #include <iostream>
// #include <memory>
// #include <string>
// #include <vector>

// using namespace std;
// using namespace std::placeholders;

// class Person {
// private:
//     int m_age;
//     float m_score;

// public:
//     // int i;
//     Person(int age, float score)
//         : m_age(age)
//         , m_score(score)
//     {
//     }

//     void test()
//     {
//         auto f1 = [this]() {
//             cout << "test: " << m_age << endl;
//         };
//         f1();
//     }
// };

// int main()
// {
//     int a = 111;
//     int b = -1;
//     auto f1 = [=](int c) mutable {
//         a += 9;
//         return a + c;
//     };

//     auto f2 = [&]() mutable {
//         b += 1;
//     };

//     f2();
//     cout << "a的值： " << a << endl;
//     cout << "b的值： " << b << endl;
//     cout << f1(3) << endl;

//     Person p(100, 122);
//     p.test();
//     return 0;
// }

/*
 * @Author: Phoenix_Z
 * @Date: 2022-10-12 14:21:17
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-10-12 14:21:17
 * @Description:
 */
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

void Func(int a, int b)
{
    cout << "a+b: " << a + b << endl;
}

int main()
{
    int a = 9, b = 10;
    auto f1 = bind(Func, _1, _2);
    f1(a, b);

    auto f2 = [&]() { Func(a, b); }; // lamda表达式代替bind绑定器
    auto f3 = [](int a, int b) { return a + b; };
    typedef int (*PFUNC)(int, int);
    PFUNC p = f3; //将lamda表达式传给函数指针
    cout << p(1, 2) << endl;

    return 0;
}