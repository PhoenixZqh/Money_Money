# 基础概念

## 日志级别

* trace  调试时打印详细信息
* info     运行时显示基本信息
* debug 调试用
* warn  运行时显示可能存在的问题
* *err*
* *critical*
* *off*
* *n_levels*

## sink(输出目标)

```xml
- 日志记录器槽，进行底层操作的类，比如格式化内容，输出内容到控制台或者文件
```

* set_pattern   自定义输出内容格式
* set_level       设置日志输出最低等级
* log                 由logger自动调用

## logger(记录器)

* set_pattern(const std::string&) ：设置logger包含的所有sink的日志输出内容格式
* set_level(level_enum) ：设置logger日志输出最低等级，如果logger包含的sink没有设置日志等级的话，则会为其设置日志等级
* log(level_enum level,log_msg content) ：按照level等级进行输出content，logger其中日志输出最低等级小于或等于level的sink会进行执行输出操作
* trace(content,arg1,arg2…) ：按照trace等级进行输出，输出内容由content与后面的参数格式化而成。同类的函数还包括：debug/info/warn

## st/mt

* **st** ：单线程版本，不用加锁，效率更高。
* **mt** ：多线程版本，用于多线程程序是线程安全的。

==注意使用多线程版本需要加锁==

# 使用spdlog

## 创建logger

```xml
1. auto my_logger= spdlog::basic_logger_mt("zqh", "/home/spdlogStudy/logs/1.txt");  #spdlog可以自动在指定路径下生成文件

2. auto logger = spdlog::rotating_logger_mt("rotate", "/home/spdlogStudy/logs/rotate.log", 1024 * 1024 * 5, 3);  #指定单个文件大小为5M，如果不满足，将会在下一个文件中写入，最大文件数为3

3. auto m_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("/home/spdlogStudy/logs/allinone.log", 1024 * 1024 * 10, 5);  #通过sink的方式创建logger
   auto m_logger1 = std::make_shared<spdlog::logger>("func1", m_sink)
```

## 设定日志级别

```cpp
#include <iostream>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"    // support for basic file logging
#include <spdlog/sinks/stdout_color_sinks.h> // 包含 stdout_color_sinks 头文件

int main()
{
    //保存日志到文件
    auto m_logger = spdlog::basic_logger_mt("log_level", "/home/spdlogStudy/logs/log_level.log");

    m_logger->set_level(spdlog::level::debug); // 设置 Logger 级别以包含 debug 消息

    m_logger->debug("测试debug:{}", 111);
    m_logger->info("测试info");
    m_logger->warn("测试warn");
    m_logger->error("测试error");

    //输出到终端
    auto console_logger = spdlog::stdout_color_mt("console");
    console_logger->set_level(spdlog::level::debug);
    console_logger->trace("\033[0;36mThis is a trace message\033[0m");
    console_logger->debug("\033[0;32mThis is a debug message\033[0m");
    console_logger->info("\033[0;37mThis is an info message\033[0m");
    console_logger->warn("\033[1;33mThis is a warning message\033[0m");
    console_logger->error("\033[0;31mThis is an error message\033[0m");
    console_logger->critical("\033[1;37;41mThis is a critical message\033[0m");
    return 0;
}
```

## 自定义格式

具体参考：  [自定义格式 ](https://github.com/gabime/spdlog/wiki/3.-Custom-formatting)

```cpp
#include <iostream>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"    // support for basic file logging
#include <spdlog/sinks/stdout_color_sinks.h> // 包含 stdout_color_sinks 头文件

int main()
{
    auto m_logger = spdlog::basic_logger_mt("diy_pattern", "/home/spdlogStudy/logs/pattern.log");
    m_logger->set_level(spdlog::level::debug);
    m_logger->set_pattern("%^[%l]%$%v");
    // m_logger->set_pattern("[%m][%d][%H]%v");

    m_logger->debug(" 测试debug:{}", 111);
    m_logger->info(" 测试info");
    m_logger->warn(" 测试warn");
    m_logger->error(" 测试error");

    return 0;
}
```

## 多个记录器保存到同一个文件

需要注意的是，当多个记录器在不同的线程中时，需要加锁

```cpp
#include <iostream>
#include <spdlog/spdlog.h>
#include "spdlog/sinks/basic_file_sink.h"    // support for basic file logging
#include <spdlog/sinks/stdout_color_sinks.h> // 包含 stdout_color_sinks 头文件
#include <spdlog/sinks/rotating_file_sink.h>
#include <thread>
#include <mutex>

// 需要注意的是多线程往一个文件中写入内容时要加锁

class Log
{
private:
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> m_sink;
    std::shared_ptr<spdlog::logger> m_logger1;
    std::shared_ptr<spdlog::logger> m_logger2;
    std::shared_ptr<spdlog::logger> m_logger3;

    std::mutex m_mutex; // 用于同步的互斥锁

    int m_tmp;

public:
    Log()
        : m_tmp(10)
    {
        //单个文件不超过10m， 最多不超过5个文件
        m_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("/home/spdlogStudy/logs/allinone.log", 1024 * 1024 * 10, 5);

        m_logger1 = std::make_shared<spdlog::logger>("func1", m_sink);
        m_logger2 = std::make_shared<spdlog::logger>("func2", m_sink);
        m_logger3 = std::make_shared<spdlog::logger>("func3", m_sink);

        m_logger1->info("\n\n---------------------开始保存log----------------------------");
    }
    ~Log() = default;

    void Func1(int tmp)
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 在记录前加锁

        while (tmp-- > 0)
        {
            m_logger1->info("{}", tmp);
        }
    }

    void Func2(int tmp)
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 在记录前加锁

        while (tmp-- > 0)
        {
            m_logger2->info("{}", tmp);
        }
    }

    void Func3(int tmp)
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 在记录前加锁
        while (tmp-- > 0)
        {
            m_logger3->info("{}", tmp);
        }
    }
};

int main()
{
    Log log;

    std::thread fun_thread([&log]() { log.Func3(10); });

    log.Func1(10);
    log.Func2(10);
    fun_thread.join();

    return 0;
}
```
