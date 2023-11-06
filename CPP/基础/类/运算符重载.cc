/*
创建Box类， 包含长宽高属性
成员函数输出Box的体积
要求： 通过运算符重载，计算两个box相加后的体积
*/

#include <iostream>
#include <memory>

using namespace std;

class Box {
public:
    int m_length;
    int m_width;
    int m_height;

    Box() {};
    Box(int length, int width, int height)
        : m_length(length)
        , m_width(width)
        , m_height(height) {};
    ~Box() {};

    Box operator+(Box& b) //类内实现 -> 成员函数
    {
        Box box;
        box.m_length = this->m_length + b.m_length;
        box.m_width = this->m_width + b.m_width;
        box.m_height = this->m_height + b.m_height;
        return box;
    }

    void show()
    {
        cout << this->m_height * this->m_length * this->m_width << endl;
    }
};

Box operator*(Box& b1, Box& b2) //类外实现， 友元函数
{
    Box box;
    box.m_length = b1.m_length * b2.m_length;
    box.m_width = b1.m_width * b2.m_width;
    box.m_height = b1.m_height * b2.m_height;
    return box;
}

int main()
{
    Box b1(1, 1, 1);
    Box b2(2, 2, 2);

    Box b3 = b1 + b2;
    b3.show();

    Box b4 = b1 * b2;
    b4.show();

    return 0;
}