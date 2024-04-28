#include <iostream>
#include <memory>

#define B

/**
 *@brief 类模板的关键字是class，类实例化的时候要指明类型 
*/

#ifdef A
template <class T1, class T2>
class Person
{
private:
    T1 name_;
    T2 age_;

public:
    Person(T1 &name, T2 &age)
        : name_(name), age_(age)
    {
    }

    void printMsg()
    {
        std::cout << this->name_ << " " << this->age_ << std::endl;
    }

    ~Person()
    {}
};

int main()
{
    std::string name = "james";
    int age = 39;
    std::shared_ptr<Person<std::string, int>> person = std::make_shared<Person<std::string, int>>(name, age);
    person->printMsg();
    return 0;
}

/**
 * @brief 类模板发生继承时，子类继承需要给定基类类型
*/

#elif defined(B)

template <class T>
class Animal
{
public:
    T num_;

    Animal(T &num)
        : num_(num)
    {}

    virtual ~Animal()
    {}

    virtual T testFunc() = 0;
};

using AnimalType = Animal<int>;
class Dog : public AnimalType
{
public:
    Dog(int &num)
        : Animal(num){};

    ~Dog()
    {}

    int testFunc()
    {
        return ++this->num_;
    }
};

int main()
{
    int num = 10;
    std::shared_ptr<Dog> dog = std::make_shared<Dog>(num);
    auto res = dog->testFunc();
    std::cout << "res: " << res << std::endl;
    return 0;
}

#endif
