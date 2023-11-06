#include <iostream>

/**
 * @brief 测试switch case 在满足条件后继续增加逻辑
 */

using namespace std;

int b, c, d;

void TestSwitch(int a)
{
    switch (a)
    {
    case 1: {
        b =  1;
        break;
    }

    case 2: {
        c = 2;
        break;
    }

    case 3: {
        d = 3;
        break;
    }

    default:
        break;
    }

    cout << "b: " << b << "\t"
         << "c: " << c << "\t"
         << "d: " << d << endl;
}

int main()
{
    int tmp;
    cout << "请输入数值" << endl;
    cin >> tmp;

    TestSwitch(tmp);
    return 0;
}