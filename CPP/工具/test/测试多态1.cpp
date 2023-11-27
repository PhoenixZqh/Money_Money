/**
 * @brief 多态不仅仅是说父类的指针或者引用指向子类对象，也可以是子类对象调用父类的函数； 对象如果调用的是虚函数，则最终调用的是该对象所属类中的虚函数
*/

#include <iostream>

using namespace std;

class Animal
{
private:
    int b = 10;

public:
    Animal(/* args */){};
    ~Animal(){};

    int local_pos = 10;

    virtual void Bark(){};

    void TestDuoTai()
    {
        Bark();
        cout << "测试父类函数是否会被调用" << endl;
    }

    int GetB()
    {
        return b;
    }
};

class Dog : public Animal
{
private:
    /* data */
public:
    Dog(/* args */){};
    ~Dog(){};

    void Bark()
    {
        cout << "汪汪往"
             << "\t" << endl;
    }
};

int main()
{
    Dog dog;

    int b = dog.GetB();
    cout << "b: " << b << endl;
    dog.TestDuoTai();
    return 0;
}
