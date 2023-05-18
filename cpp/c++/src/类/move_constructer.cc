/*
 * @Author: Phoenix_Z
 * @Date: 2022-09-28 19:17:44
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-09-28 19:17:44
 * @Description: 理解为什么要使用移动构造？移动构造函数原理？移动构造函数使用？
 */

#include <cstring>
#include <iostream>
#include <memory>

using namespace std;

class MyString {
private:
    char* m_str;
    int m_len;

public:
    MyString(char* str) //普通构造函数
    {
        m_len = strlen(str);
        m_str = new char[m_len + 1];
        m_str = strcpy(m_str, str);
        cout << "普通构造函数， str = " << str << endl;
    }
    MyString(const MyString& tmp) //拷贝构造函数
    {
        cout << "tmp的地址： " << (void*)&tmp << endl;
        m_len = tmp.m_len;
        m_str = new char[m_len + 1];
        m_str = strcpy(m_str, tmp.m_str);
        cout << "拷贝构造函数 , str = " << tmp.m_str << endl;
    }

    MyString& operator=(const MyString& tmp)
    {
        if (&tmp == this)
            return *this;
        m_len = 0;
        delete[] m_str;
        m_len = tmp.m_len;
        m_str = new char[m_len + 1];
        m_str = strcpy(m_str, tmp.m_str);
        return *this;
    }
    MyString(MyString&& t)
    {
        cout << "t的地址： " << (void*)&t << endl;
        m_str = t.m_str;
        m_len = t.m_len;

        t.m_str = nullptr;
        cout << "移动构造函数" << endl;
    }

    ~MyString()
    {
        cout << "析构函数";
        if (m_str != nullptr) {
            delete[] m_str;
            m_len = 0;
            cout << "已操作delete";
        }
        cout << endl;
    }
    void show()
    {
        cout << m_str << "长度为： " << m_len << endl;
    }
};

MyString func()
{
    MyString obj("james");
    cout << "obj地址： " << (void*)&obj << endl;
    return obj; //在这里会创建一个临时对象，调用拷贝构造函数
}

int test()
{
    static int a = 10;
    return a;
}

int main()
{
    // int&& b = test(); //右值引用， 引用是给变量取别名，右值引用就是给字面常量、表达式、函数非引用返回值取别名
    // cout << "b: " << b << endl;

    // int&& c = 20;
    // cout << "c: " << c << endl;

    int a = test();
    int&& b = move(a);
    cout << b << endl;

    // MyString mstr = func();
    MyString&& mstr1 = func(); //移动构造，相当于只是过度一下，没有开辟新的空间 //在这里调用后，临时对象会释放掉，因此调用析构函数
    // mstr1.show();
    return 0;
}
