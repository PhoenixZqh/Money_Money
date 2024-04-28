/*
 * @Author: Phoenix_Z
 * @Date: 2022-09-03 14:42:35
*/

#include <iostream>
#include <memory>

using namespace std;

int add(int a, int b)
{
    return a + b;
}

int test(int a, int b, int (*pf)(int, int)) //函数指针的写法，与要用的函数返回类型，参数列表一致
{
    cout << (*pf)(a, b) << endl;
    return (*pf)(a, b);
}

int main()
{
    auto pf = add; // pf 是函数指针 ， *pf 是函数 ， 函数名即是函数地址
    test(3, 4, pf);
    return 0;
}