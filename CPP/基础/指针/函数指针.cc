/*
 * @Author: Phoenix_Z
 * @Date: 2022-09-03 14:42:35
 * @Last Modified time: 2024-04-27
 * @Description: function pointer
 
 ? 1. 程序如果定义了一个函数，在编译时就会为这个函数分配一段储存空间； 这段储存空间的首地址称为这个函数的地址，函数名表示这个地址
 ? 2. 指向函数地址的指针称为函数指针
 ? 3. 函数返回类型 （*函数指针名）（参数列表）
*/



#include <iostream>
#include <memory>

#define NONE
/**
 * @brief 函数指针作为函数的参数
*/

 
using namespace std;

#ifdef AS_ARGS

int returnNum()
{
    return 30;
}

void showNum( int(*getNum)())
{
    auto num = getNum();
    std::cout << "get num : " << num << std::endl;
}

int main()
{
    showNum(returnNum);
    return 0;
}

#elif defined(AS_RETURN_VALUE)

/**
 * @brief 函数指针作返回值
*/
int addVal(int a, int b)
{
    return a+b;
}

int decreaseVal(int a, int b)
{
    return a-b;
}

int (*getNum(char op))(int,int)
{
    if(op == '+')
    {
        return addVal;
    }

    else if(op == '-')
    {
        return decreaseVal;
    }
    
    else
    {
        return NULL;
    }

}

int main()
{
    char op = '-';
    int (*Func)(int,int) = getNum(op);

    auto res = Func(10,20);
    std::cout << "res: " << res << std::endl;
    return 0;
}

#else

/**
 * @brief 函数指针实现回调函数
*/
int add(int a, int b)
{
    return a+b;
}

int test(int a, int b, int (*pf)(int,int))    //函数指针的写法，与要用的函数返回类型，参数列表一致
{   
    return (*pf)(a, b);                 
}
 
int main()
{   
    std::cout << "Address of add function: " << reinterpret_cast<void*>(add) << std::endl;
    auto res = test(3,4,add);
    std::cout << "res: " << res << std::endl;
    return 0;
}

#endif