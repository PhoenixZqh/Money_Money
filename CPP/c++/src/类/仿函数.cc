/*
 * @Author: Phoenix_Z
 * @Date: 2022-10-11 10:15:38
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-10-11 10:33
 * @Description: 仿函数示例
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Person {
private:
    char* m_name;
    int m_age;

public:
    Person() = default;
    Person(char* name, int age)
        : m_name(name)
        , m_age(age)
    {
    }
    ~Person() = default;

    void operator()()
    {
        cout << "姓名： " << m_name
             << "\n"
             << "年龄： " << m_age
             << endl;
    }
};

int main()
{
    Person p("james", 19);
    p(); //调用仿函数， 使得类具有函数的功能
    return 0;
}