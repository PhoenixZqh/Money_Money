/*
 * @Author: Phoenix_Z
 * @Date: 2022-11-22 14:50:53
 * @Last Modified by: Phoenix_Z
 * @Last Modified time:
 * @Description:
 */

/*
delete 会调用析构函数， 析构函数中又调用了delete ， 就会引起循环；
*/

#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::placeholders;

class Person {
private:
    Person() { } // 创建私有构造函数

public:
    static Person* p;

    void show()
    {
        cout << "***设计单例模式***" << endl;
    }

    static Person* getP()
    {
        if (p == nullptr) {
            p = new Person();
            static Delete d1; //这里是个什么玩意儿？
        }

        return p;
    }

    class Delete { //嵌套类
    public:
        ~Delete()
        {

            if (Person::p) {
                cout << "嵌套类的析构函数调用" << endl;
                delete Person::p;
                p == nullptr;
            }
        }
    };
};

Person* Person::p = nullptr; //静态成员变量在类外进行初始化

int main()
{

    Person* p_ = Person::getP();
    Person* p2 = Person::getP();
    p_->show();
    return 0;
}