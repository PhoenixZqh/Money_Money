// /*
//  * Author: phoenixZ
//  * Date: 2024-04-17 14:58:55
//  * Description: std::function 包装（函数、函数指针、成员函数、lambda表达式等）， 并提供统一的调用接口
// */

// #include <iostream>
// #include <functional>

// typedef std::function<void(int)> process;

// void func1(int a)
// {
//     std::cout << "a: " << a << std::endl;
// }

// void func2(int b)
// {
//     std::cout << "b: " << b << std::endl;
// }

// void func3(int c)
// {
//     std::cout << "c: " << c << std::endl;
// }

// // 调用
// void testFunc(int num, std::function<void(int)> process)
// {
//     process(num);
// }

// int main()
// {
//     process p;

//     std::cout << "please input a num: " << std::endl;
//     int a;
//     std::cin >> a;

//     switch (a)
//     {
//     case 1: {
//         p = func1;
//         break;
//     }
//     case 2: {
//         p = func2;
//         break;
//     }

//     default:
//         break;
//     }

//     testFunc(a, p);
//     return 0;
// }

#include <iostream>
#include <functional>

template <typename... Args>
std::function<void(int, Args...)> Func = [](int, Args... args) {
    // 注意这里将参数传递到 lambda 表达式中
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
};

int main()
{
    // 使用示例
    Func<int, float>(2, 3.14f, 42);
    // Func<double, const char *>(2, 3.14, " is a pi");
    return 0;
}
