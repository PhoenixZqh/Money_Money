
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::placeholders;

//创建线程入口，一个线程存数据，一个线程取数据

class Person {
private:
    list<int> res;
    mutex my_mutex;

public:
    void SaveData()
    {
        for (int i = 0; i < 1000000; ++i) {
            my_mutex.lock(); //加锁
            res.push_back(i);
            my_mutex.unlock(); // 解锁
            cout << "存储数据" << i << endl;
        }
    }

    bool JudgeOut(int commond)
    {
        // my_mutex.lock();
        lock_guard<mutex> sbguard(my_mutex); // lock_guard()用法

        if (!res.empty()) {
            commond = res.front();
            res.pop_front();
            // my_mutex.unlock(); //这里为什么需要再加一个unlock？只要往外退就得对应unlock一次，不然就锁住了
            return true;
        }
        // my_mutex.unlock();

        return false;
    }

    void OutData()
    {
        for (int i = 0; i < 1000000; ++i) {

            bool result = JudgeOut(0);
            if (result) {
                cout << "取数据" << i << endl;
            }

            else {
                cout << "消息队列为空" << i << endl;
            }
        }
    }
};

int main()
{
    Person p1;
    thread t1(&Person::SaveData, &p1);
    thread t2(&Person::OutData, &p1);
    t1.join();
    t2.join();

    return 0;
}