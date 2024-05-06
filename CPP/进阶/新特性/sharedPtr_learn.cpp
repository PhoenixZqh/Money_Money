#include <iostream>
#include <memory>

using namespace std;

class Student
{
public:
    char *m_name;
    Student(char *name)
        : m_name(name){};
    ~Student()
    {
        cout << "im:" << m_name << ","
             << "destroied" << endl;
    }
};

int main()
{
    char *name = "james";
    shared_ptr<Student> p1 = make_shared<Student>(name); //创建shared_ptr
    shared_ptr<Student> p2(p1);
    shared_ptr<Student> p3 = p2;

    Student *p = p3.get(); //将智能指针(类)指向的地址传递给指针

    cout << p->m_name << "," //指向同一块堆区，所以析构函数此时只调用一次
         << p1->m_name << ", "
         << p2->m_name << ", "
         << p3->m_name << "\n"
         << "p3 count:" << p3.use_count() << ", " //use_count()计数
         << endl;

    p1.reset(new Student("kobe")); //此时p1改变了指向的地址
    cout << p1->m_name << endl;
    cout << "p1 after changed:" << p1.use_count() << endl;
    cout << "p3 count after p1 changed:: " << p3.use_count() << endl;

    p2.reset();
    cout << "p3 count after p2 changed:" << p3.use_count() << endl;

    return 0;
}

/*
运行结果：
james,james, james, james
p3 count:3, 
kobe
p1 after changed:1
p3 count after p1 changed:: 2
p3 count after p2 changed:1
im:james,destroied
im:kobe,destroied
*/
