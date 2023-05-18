/*
 * @Author: Phoenix_Z
 * @Date: 2022-10-29 16:21:21
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-10-29 16:21:21
 * @Description:
 */

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

/*
常量指针： 指针指向是常量， 值不可以修改，但是地址可以修改
指针常量： 指针本身是常量， 指针指向的地址不可修改，指向的值可改
*/

class Func {
private:
    int m_a;

public:
    void test(int b) const
    {
        b = 22;
    }
};

class Person {
private:
    const int m_age;

public:
    static const int m_score;
    Person(int age)
        : m_age(age)
    {
    }

    const void show()
    {
        cout << "m_age" << m_age << endl;
    }
};

const int Person::m_score = 10;

int main()
{
    int a = 0, b = 1;
    cout << "常量指针初始化的指：" << a << endl;
    const int* p1 = &a;
    // *p1 = b;  err：常量指针指向的值不可修改
    p1 = &b;
    cout << "常量指针改变地址后的值： " << *p1 << endl;

    int* const p2 = &b;
    *p2 = a;
    // p2 = &a;   err: 指针常量的地址不可修改
    cout << "指针常量改值后： " << *p2 << endl;

    Person p(11);
    p.show();
    cout << p.m_score << endl;

    return 0;
}