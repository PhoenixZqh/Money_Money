#include <iostream>

#define C

/**
 1. 模板是在编译时实例化的，编译器根据根据实际情况生成对应的代码
 2. 由模板示例化后的函数称为模板函数
*/

/**
 * @brief 返回类型和参数使用不同的模板，在调用时需要指定类型
*/
#ifdef A

template <typename T1, typename T2>
T1 Func(T2 &a, T2 &b)
{
    std::cout << a << " " << b << std::endl;
    return T1();
}

int main()
{
    int a = 10, b = 8;
    Func<int>(a, b);

    return 0;
}

/**
 *@brief  最直接的使用方式
*/

#elif defined(B)
template <typename T>
void Func(T &a, T &b)
{
    std::cout << a << " " << b << std::endl;
}

int main()
{
    int a = 20, b = 85;
    Func(a, b);

    return 0;
}

/**
 * @brief 共用一个模板，调用时不需要指定类型
*/

#elif defined(C)
template <typename T>
T Func(T &a, T &b)
{
    return a > b ? a : b;
}

int main()
{
    int a = 20, b = 85;
    auto res = Func(a, b);

    std::string a1 = "james", b1 = "kobe";
    auto res1 = Func(a1, b1);
    std::cout << res1 << std::endl;

    return 0;
}

#endif
