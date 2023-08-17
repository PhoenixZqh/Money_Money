
#include <condition_variable>
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

/*

1. 创建两个线程，分别往列表里面写和取数据
2. 设置条件变量判断
3. 使用unique_lock() 和 lock_guard(),清楚两者区别
*/

class HandleData {
private:
    list<int> data_;
    mutex my_mutex;
    condition_variable my_cond;
    int max_size_ = 1000000;

    bool IsFull()
    {
        lock_guard<mutex> lock(my_mutex);
        return data_.size() == max_size_;
    }

public:
    // list<int> data_;

    void TakeData()
    {
        for (int i = 0; i < 1000000; ++i) {
            unique_lock<mutex> lock(my_mutex);
            my_cond.wait(lock, [this] { return !data_.empty(); });
            cout << "***取出数据***" << data_.front() << endl;
            data_.pop_front();

            lock.unlock();
            my_cond.notify_one();
        }
    }

    void PutData()
    {

        for (int i = 0; i < 1000000; ++i) {

            unique_lock<mutex> lock(my_mutex);
            // my_cond.wait(lock, [this] { return !IsFull(); });
            cout << "存入数据 --> " << i << endl;
            data_.push_back(i);
            lock.unlock();
            my_cond.notify_one();
        }
    }

    // void Init()
    // {
    //     lock_guard<mutex> lock(my_mutex);
    //     cout << "init" << endl;

    //     for (int i = 0; i < 10; ++i) {
    //         cout << "存" <<
    //         data_.push_back(i);
    //     }

    //     my_cond.notify_one();
    // }
};

int main()
{
    mutex mutex2;
    HandleData hd;
    // thread t(&HandleData::Init, &hd);
    thread t1(&HandleData::PutData, &hd);
    thread t2(&HandleData::TakeData, &hd);

    // t.join();
    t1.join();
    t2.join();
    cout << "perfect!" << endl;
    return 0;
}
