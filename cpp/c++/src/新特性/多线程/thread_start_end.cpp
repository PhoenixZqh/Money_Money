#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::placeholders;

/*
1. 创建的线程，也需要从一个函数开始运行，一旦这个函数执行完毕，创建的线程就运行结束
2. 进程结束的标志是主线程结束，此时子线程会强行中断，如果想让子线程继续运行，则需要报纸主线程的运行状态
3. thread 是标准库中的类
4. join，阻塞主线程，让主线程等待子线程执行完
*/

void MyThread()
{
    cout << "我的线程开始了" << endl;

    cout << "我的线程结束了" << endl;
}

class Person {
private:
    /* data */
public:
    void operator()() //仿函数
    {
        cout << "person线程开始执行" << endl;

        cout << "person线程结束" << endl;
    }
};

int main()
{

    thread t1(MyThread);
    if (t1.joinable()) {
        t1.join();
    }

    Person p1;
    thread t2(p1);
    t2.join();

    cout << "I am main thread" << endl;
    return 0;
}