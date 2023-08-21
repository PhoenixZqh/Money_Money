
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::placeholders;

int main()
{
    double tmp = 15.222222222;
    int test = tmp * 1e7;
    cout << ": " << tmp << "\t" << test << endl;
    return 0;
}