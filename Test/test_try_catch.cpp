#include <iostream>
#include <string>
#include <exception>

using namespace std;

/**
 * @brief 捕获异常用try——catch 语法，抛出的异常需要是明确的，如果不明确，会捕获不到； 如果try里面有异常try中后面的代码都不会执行
*/
void GetException()
{
    string str = "http://c.biancheng.net";

    try
    {
        char ch1 = str[100]; //下标越界，ch1为垃圾值
        cout << ch1 << endl;
    }
    catch (const std::exception &e)
    {
        cout << "第一个" << endl; //第一个异常捕获不到，因为异常不明确， ch1没有意义
        std::cerr << e.what() << '\n';
    }

    try
    {
        char ch2 = str.at(100); //下标越界，抛出异常
        cout << ch2 << endl;
    }
    catch (const std::exception &e) //捕获的是标准类型的异常
    {
        cout << "第2个" << endl;

        std::cerr << e.what() << '\n';
    }

    cout << "执行结束" << endl;
}

void Func1()
{
    throw "func1 出现异常";
    cout << "测试func1后面代码是否会继续执行" << endl;
}

/**
 * @brief 定位异常发生的位置， throw关键字用来抛出异常； 
*/
void LocateException()
{
    try
    {
        Func1();
        cout << "测试try后面代码是否会继续执行" << endl;
    }
    catch (const char *&e) //捕获一些字符串异常
    {
        std::cout << e << std::endl;
    }
}

int main()
{
    GetException();
    LocateException();
    return 0;
}