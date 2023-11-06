#include <glog/logging.h>
#include <iostream>

void testGlog()
{
    static int index = 0;

    while (1) {
        index++;
        LOG(INFO) << "test index : " << index;
    }
}

int main(int argc, char* argv[])
{
    google::InitGoogleLogging(argv[0]);
    FLAGS_log_dir = "/home/zqh/phoenixZ/Money_Money/CPP/c++/src/工具类/test/";
    FLAGS_logtostderr = false; // 禁用终端输出

    testGlog();

    google::ShutdownGoogleLogging();
    return 0;
}
