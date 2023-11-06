/*
 * @Author: Phoenix_Z
 * @Date: 2022-10-09 16:35:25
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-10-09 16:35:25
 * @Description: 基类中创建一个虚方法, 子类重新定义这个需方法
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Animal {
private:
    string m_bark;

public:
    Animal(string bark)
        : m_bark(bark)
    {
    }
    virtual ~Animal() { }

    virtual void Bark()
    {
        cout << "基类方法: " << m_bark << endl;
    }
};

class Dog : public Animal {
private:
    string m_attribute;

public:
    Dog(string attribute, string dog_bark)
        : m_attribute(attribute)
        , Animal(dog_bark)
    {
    }
    ~Dog() { }

    virtual void Bark()
    {
        cout << "子类方法: " << m_attribute << endl;
    }
};

class Cat : public Animal {
private:
    string m_attribute;

public:
    Cat(string attribute, string dog_bark)
        : m_attribute(attribute)
        , Animal(dog_bark)
    {
    }
    ~Cat() { }

    virtual void Bark()
    {
        cout << "子类方法: " << m_attribute << endl;
    }
};

int main()
{
    Dog dog("狗", "汪汪汪");

    Animal* ani = &dog;
    ani->Bark();

    Cat cat("猫", "喵喵喵");
    Animal& an1 = cat;
    an1.Bark();

    return 0;
}
