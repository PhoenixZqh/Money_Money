
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

inline int show(int a, int b, int c) { return a * b * c; }

int main()
{

    clock_t start, end;

    int a = 3, b = 4;
    start = clock();

    cout << show(a, b, 9) << endl;
    end = clock();
    cout << "Run time: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;

    return 0;
}