#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 这个函数的作用是将2,3,4数组，变成2x3x4
string join_dims(const vector<int>& dims)
{
    stringstream output;
    char buf[64];

    const char* fmts[] = { "%d", " x %d" };

    for (int i = 0; i < dims.size(); ++i) {
        snprintf(buf, sizeof(buf), fmts[i != 0], dims[i]); // i!=0,表示从第二个数开始
        output << buf;
    }

    return output.str();
}

int main()
{
    int a, b, c;
    vector<int> dims;

    cout << "请输入3个数字" << endl;
    cin >> a >> b >> c;

    dims.push_back(a);
    dims.push_back(b);
    dims.push_back(c);

    string res = join_dims(dims);
    cout << res << endl;
}
