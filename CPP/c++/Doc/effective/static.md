# 静态变量

| 类型         | 特点                                                                                                                      |
| ------------ | ------------------------------------------------------------------------------------------------------------------------- |
| 普通局部变量 | <font color = green> 存储在进程栈空间，函数返回后会立即释放；如果没有给定初始值，系统会随机赋一个值 </font>               |
| 静态局部变量 | <font color = green> 即使没有初始化，编译器也会将其初始化为0；存储于全局区域，即使函数返回，其值也不会变 </font>          |
| 静态全局变量 | <font color = green> 静态全局变量仅对当前文件可见，其他文件不可访问，其他文件可以定义与其同名的变量，两者互不影响 </font> |

```cpp
void TestStatic()
{
    int a = 0;
    static int b = 0;
    cout << "a++: " << a++
         << "\t"
         << "b++: " << b++
         << endl;
}

int main()
{

    Person p(22, 98.9);
    auto funcPtr = &Person::add;

    int n = 5;
    while (n--) {
        TestStatic();
    }

    return 0;
}

输出：
a++: 0  b++: 0
a++: 0  b++: 1
a++: 0  b++: 2
a++: 0  b++: 3
a++: 0  b++: 4

```

# 静态成员

1. 静态成员变量
   ```xml
   由于声明为static的变量只被初始化一次，因为它们在单独的静态存储中分配了空间，因此类中的静态变量由对象共享。
   对于不同的对象，不能有相同静态变量的多个副本。也是因为这个原因，静态变量不能使用构造函数初始化。
   ```
   ==也就是说，类中声明为静态的成员变量，不能通过构造函数初始化，类外定义该静态成员变量，可以被所有对象共享==

2. 静态成员函数
   a. 可以使用对象和'.'调用静态成员函数，但是用静态成员函数的作用阈调用更好！
   b. 静态成员函数仅能访问静态数据成员或其他静态成员函数
   c. 没有this指针
   

3. 静态类对象
   直到程序的生命周期结束

```cpp
/*
 * @Author: Phoenix_Z
 * @Date: 2022-11-09 11:30:26
 * @Last Modified by: Phoenix_Z
 * @Last Modified time: 2022-11-09 11:30:26
 * @Description:
 */

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

class Person {
private:
    int m_age;
    float m_score;

public:
    static int m_i; //静态成员变量

    static int add(int a, int b)
    {
        return a + b;
    }

    Person(int a, int b)
        : m_age(a)
        , m_score(b)
    {
        cout << "im constructor" << endl;
    }

    Person() = default;

    ~Person()
    {
        cout << "im destructor" << endl;
    }

    void show(int a, int b, int (*funcptr)(int, int))
    {
        cout << (*funcptr)(a, b) << endl;
    }

    void show1(int a, int b, function<int(int, int)> f1)
    {
        cout << f1(a, b) << endl;
    }
};

void TestStatic()
{
    int a = 0;
    static int b = 0;
    cout << "a++: " << a++
         << "\t"
         << "b++: " << b++
         << endl;
}

int main()
{

    Person p;
    auto funcPtr = &Person::add; //设置add函数的指针
    p.show(22, 22, funcPtr);

    auto f1 = bind(&Person::add, _1, _2); //使用bind绑定器
    p.show1(2, 3, f1);

    int n = 5;
    while (n--) {
        TestStatic();
    }

    if (1) {
        static Person p1(1, 1.2); //加了static ，作用阈在全局，而不在if循环内，所以先end然后析构
    }

    cout << "end!" << endl;

    return 0;
}
```
   