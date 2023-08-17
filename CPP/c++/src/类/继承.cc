/*
 * @Author: Phoenix_Z
 * @Date: 2022-10-09 09:45:24
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-10-09 09:45:24
 * @Description:创建一个动物类，基类包含动物的身高体重， 派生类添加各个动物的叫声（属性）
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Animal {
private:
    float m_height;
    int m_weight;
    char* m_attribute;

public:
    Animal(float height, int weight, char* attribute)
        : m_height(height)
        , m_weight(weight)
        , m_attribute(attribute)

    {
        cout << "基类构造函数调用" << endl;
    }

    Animal(Animal& a)
    {
        m_height = a.m_height;
        m_weight = a.m_weight;
        m_attribute = a.m_attribute;
    }

    Animal(Animal&& Ani)
    {
        m_height = Ani.m_height;
        m_weight = Ani.m_weight;
        m_attribute = Ani.m_attribute;

        Ani.m_height = 0;
        Ani.m_weight = 0;
        Ani.m_attribute = nullptr;
        cout << "移动构造函数调用" << endl;
    }

    Animal& operator=(const Animal& tmp)
    {
        if (&tmp == this)
            return *this;

        m_height = 0;
        m_weight = 0;
        m_attribute = nullptr;

        m_height = tmp.m_height;
        m_weight = tmp.m_weight;
        m_attribute = tmp.m_attribute;
        return *this;
    }

    ~Animal()
    {
        cout << "基类析构函数调用";
        if (m_attribute != nullptr) {
            m_attribute = nullptr;
            delete[] m_attribute;
            m_height = 0;
            m_weight = 0;
        }
        cout << "delete done" << endl;
    }
    void show()
    {
        cout << m_attribute << "-->"
             << "身高：" << m_height << "m"
             << "  "
             << "体重： " << m_weight << "kg"
             << endl;
    }
};

class Dog : public Animal {
private:
    string m_bark;

public:
    Dog(string bark, float dog_height, int dog_weight, char* dog_attribute)
        : m_bark(bark)
        , Animal(dog_height, dog_weight, dog_attribute)
    {
        cout << "子类构造函数调用" << endl;
    }
    Dog(string bark, Animal& ani) //通过拷贝构造函数初始化基类
        : m_bark(bark)
        , Animal(ani)
    {
    }

    ~Dog()
    {
        cout << "子类析构函数调用" << endl;
    }
    void Bark()
    {
        cout << m_bark << endl;
    }
};

Animal Func()
{
    Animal a1(1.2, 33, "狮子");
    return a1;
}

int main()
{
    Dog dg("汪汪汪", 1.2, 40, "狗");
    Animal* p_ani = &dg; //父类的指针或引用指向子类对象
    // p_ani->show();
    dg.Bark();
    dg.show(); //子类对象调用父类的方法

    // Animal a1(1.1, 33, "喵喵");
    Animal a1 = Func();
    Dog dg1("喵喵喵", a1);
    dg1.show();

    // Animal&& a1 = Func();          //移动构造是在需要new出空间的时候有帮助
    // Dog dg2("嗷嗷嗷", a1);
    // dg2.show();
    return 0;
}