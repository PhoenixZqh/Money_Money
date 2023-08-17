#include "learn_exception.h"
#include <functional>

using namespace std;
using namespace std::placeholders;

int Func(int a, int b)
{
    if (b == 0) {
        throw ZqhErr("你说的不对");
    }
    return a / b;
}

int main()
{
    cout << "请输入x, y的值" << endl;

    int x, y;
    cin >> x
        >> y;

    try {
        int c = Func(x, y);
        cout << "c的值是:" << c << endl;
    } catch (ZqhErr& e) { // catch去捕获异常
        cout << e.what() << endl;
        return -1;
    }

    return 0;
}