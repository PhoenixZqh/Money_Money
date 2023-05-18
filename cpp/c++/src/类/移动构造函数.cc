/*
 * @Author: Phoenix_Z
 * @Date: 2022-09-29 10:11:06
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-09-29 10:11:06
 * @Description: move constructor
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
        m_str = str;
        m_len = strlen(str);
        cout << "普通构造函数调用" << endl;
    }

    MyString(const MyString& obj) //拷贝构造函数
    {
        cout << "拷贝对象obj的地址： " << (void*)&obj << endl;
        m_len = obj.m_len;
        m_str = new char[m_len + 1];
        m_str = strcpy(m_str, obj.m_str);
        cout << "拷贝构造函数调用" << endl;
    }

    MyString(MyString&& t)
    {
        cout << "移动对象t的地址：" << (void*)&t << endl;
        m_str = t.m_str;
        m_len = t.m_len;

        t.m_str = nullptr;
        t.m_len = 0;
        cout << "移动构造函数调用" << endl;
    }

    MyString& operator=(const MyString& tmp)
    {
        if (&tmp == this)
            return *this;

        m_len = 0;
        m_str = nullptr;

        m_len = tmp.m_len;
        m_str = strcpy(new char[m_len + 1], tmp.m_str);
        return *this; //返回MyString对象
    }

    ~MyString()
    {
        cout << "析构函数调用";
        if (m_str != nullptr) {
            m_str = nullptr;
            delete[] m_str;
            m_len = 0;
            cout << ", delete操作完成";
        }

        cout << endl;
    }

    void show()
    {
        cout << m_str << ": " << m_len << endl;
    }
};

MyString func()
{
    MyString obj("phoenix");
    return obj;
}

int main()
{
    // MyString mstr = func();
    MyString&& mstr1 = func();
    mstr1.show();
    return 0;
}