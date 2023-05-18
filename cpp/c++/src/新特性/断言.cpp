
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

int main()
{

    // bool flag = false;
    // assert(flag == true);
    // assert(flag == false);

    const int test = 100;
    static_assert(test == 100, "test not 100");

    cout << "test assert" << endl;
    return 0;
}