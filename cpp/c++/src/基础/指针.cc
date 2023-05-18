#include <iostream>

using namespace std;

class Pointer
{
private:
    int m_a;
    int * p;

public:
    Pointer(int a)
    {
        m_a = a;              
        p = new int(m_a);     //指针的初始化
    }
    
    ~Pointer()
    {
        if(p != nullptr)
        {
            delete p;         //利用析构函数进行delete
            p = nullptr;
        }
    }

    void print()
    {
        cout << "指针名" << p 
             << "指针解引用：" << *p
             << "常规变量地址：" << &m_a 
             << endl;
    }

};

void test_ponter_array()
{
    int arr[3] = {4,5,6};
    
    int *  p = arr;     // 动态数组指针p，指向的是数组的首地址
    // int *p = new int[3];
    // delete [] p;

    cout << "p[1]:" << p[1] << "\n"
         << "p:" <<  p << "\n"
         << "p+1:" << p+1           //地址后移
         << endl;
    

    
    cout << "arr: " << arr << "\n"
         << "*arr: " << *arr << "\n"
         << "size of : " << sizeof(arr)/sizeof(int)
         << endl;

}

int main()
{
    int test = 3;
    Pointer p(test);
    p.print();

    int * point = new int(test);
    cout << point << endl;

    
    test_ponter_array();
    delete point;

    struct Class
    {
        int a;
        char * name;

    };

    Class *Cl = new Class;


    
    return 0;
}
