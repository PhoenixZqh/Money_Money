#include <iostream>

using namespace std;

struct Person
{
    char * name;
    int age;
    float score;
}p1;

void Print(Person p)
{
    cout << "姓名：" << p.name << " "
         << "年龄: " << p.age  << " "
         << "得分: " << p.score << " "
         << endl;
}

int main()
{
    
    Person p2 = {"james", 18, 92.2};
    Person *p3 = new (Person);
    
    // cout << "姓名：" << p1.name << " "
    //      << "年龄: " << p1.age  << " "
    //      << "得分: " << p1.score << " "
    //      << endl;

    Person p4[100];
    p4[0] = {"kobe",19, 99.1};
    cout << "姓名：" << p4[0].name << " "
         << "年龄: " << p4[0].age  << " "
         << "得分: " << p4[0].score << " "
         << endl;

    Print(p2);




    return 0;
}