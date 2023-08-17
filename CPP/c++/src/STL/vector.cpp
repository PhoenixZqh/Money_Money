
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::placeholders;

class Person {
public:
    int m_age;

public:
    Person(int age)
        : m_age(age)
    {
    }
};

// 存储基础类型
void Test01(int* arr)
{
    vector<int> vec1;
    vec1.clear();

    vec1.push_back(arr[0]);
    vec1.push_back(arr[1]);
    vec1.push_back(arr[2]);
    vec1.push_back(88);

    vec1.assign(vec1.begin(), vec1.begin() + 2); // 将区间的值赋给本身

    auto startPtr = vec1.begin();
    auto endPtr = vec1.end();

    while (startPtr != endPtr) {
        cout << *startPtr << endl;
        startPtr++;
    }
}

// 存储类对象
void Test02()
{
    vector<Person*> vec2;
    Person* p1 = new Person(10);
    Person* p2 = new Person(20);
    Person* p3 = new Person(30);
    vec2.push_back(p1);
    vec2.push_back(p2);
    vec2.push_back(p3);

    auto startPtr = vec2.begin();
    auto endPtr = vec2.end();

    while (startPtr != endPtr) {
        cout << (*startPtr)->m_age << endl;
        startPtr++;
    }
}

// 容器嵌套容器
void Test03()
{
    vector<vector<int>> vec3;
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;

    for (int i = 0; i < 10; i++) {
        v1.push_back(i);
        v2.push_back(i * 3);
        v3.push_back(i * 5);
    }

    vec3.push_back(v1);
    vec3.push_back(v2);
    vec3.push_back(v3);

    for (auto itPtr = vec3.begin(); itPtr != vec3.end(); itPtr++) {
        for (auto it = (*itPtr).begin(); it != (*itPtr).end(); it++) {
            cout << *it << endl;
        }
    }
}

int main()
{
    int arr[3];
    cout << "please input 3 num" << endl;
    int a, b, c;
    cin >> a >> b >> c;

    arr[0] = a;
    arr[1] = b;
    arr[2] = c;

    Test01(arr);

    Test02();
    Test03();
    return 0;
}