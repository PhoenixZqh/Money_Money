#include <iostream>

/**
 * @brief  constexpr 关键字用于将函数或者变量声明为常量表达式，它可以在编译期间求值
 */

using namespace std;

int len_foo()
{
    int i = 2;
    return i;
}

constexpr int len_constexpr()
{
    int i = 3;
    return i;
}

int main()
{

    char arr1[len_foo() + 1];
    char arr2[len_constexpr() + 2];

    return 0;
}