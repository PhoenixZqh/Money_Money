#include <iostream>

using namespace std;

int main()
{
    int test;
    cout << "请输入: " << endl;
    cin >> test;

    bool res = test;

    if (res)
    {
        cout << "yes" << endl;
    }

    else
    {
        cout << "no" << endl;
    }
}