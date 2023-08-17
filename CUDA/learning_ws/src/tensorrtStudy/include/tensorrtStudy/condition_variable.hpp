
#include <condition_variable>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::placeholders;

void Condition_Variable_Test()
{
    condition_variable cv_;
    mutex lock_;
    atomic<bool> running_ { true };

    auto func = [&](int tid) {
        cout << "Async thread start. tid = " << tid << endl;

        unique_lock<mutex> ul_(lock_);

        cout << tid << ". "
             << "wait signal" << endl;

        cv_.wait(ul_, [&]() {
            printf("%d. 如果返回false，则继续等待，返回true退出等待\n", tid);
            return !running_;
        });

        printf("%d. done.\n", tid);
    };

    std::thread t0(func, 0);
    this_thread::sleep_for(chrono::seconds(3));
    printf("Notify one 1.\n");
    cv_.notify_one();

    this_thread::sleep_for(chrono::seconds(3));
    running_ = false;
    printf("Notify one 2.\n"); // 1
    cv_.notify_one(); // 2
    t0.join();
}