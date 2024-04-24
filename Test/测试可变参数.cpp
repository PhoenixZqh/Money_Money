// #include <iostream>
// #include <functional>

// using namespace std::placeholders;


// template <typename T1, typename T2, typename T3>
// void printArgs(T1 &t1,T2&t2,T3&t3)
// {
//     std::cout << t1 << " " << t2 << " " << t3 << std::endl;
// }




// int main()
// {   
//     int a =100;
//     std::string str = "test";
//     float b = 1.1;
//     auto test = std::bind(printArgs<decltype(_1), decltype(_2), decltype(_3)>,_1,_2,_3);
//     test(a,str,b);

//     return 0;
// }

#include <iostream>
#include <functional>

// 原始函数
void greet(const auto& t1, const auto& t2, const auto& t3) {
    std::cout << t1 << " " << t2   << std::endl;
}

int main() {
    // 对函数和参数进行绑定
    auto printArgs = [](auto&&... args) { greet(std::forward<decltype(args)>(args)...); };

    auto test = std::bind(printArgs, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

    test(3.0, "123", nullptr);   

    return 0;
}
