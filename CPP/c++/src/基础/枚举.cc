#include <iostream>

using namespace std;


enum Color {red, orange, yellow, green, blue, purple, pink}; //不能是整型，不能是字符常量

int main()
{

    int k = 2;        //比较时，
    if(k == yellow)
    {
        cout << "find" << endl;
    }
    else
    {
        cout << "failed" << endl;
    }
    return 0;
}