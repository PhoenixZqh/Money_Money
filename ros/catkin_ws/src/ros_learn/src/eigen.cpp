
#include <Eigen/Core>
#include <Eigen/Dense>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using namespace std::placeholders;
using namespace Eigen;

int main()
{
    MatrixXd m(3, 3); // MatrixXd 表示的是动态数组，初始化的时候指定数组的行数和列数
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            m(i, j) = i + 5;
        }
    }

    MatrixXd H = m.topLeftCorner(2, 2);
    MatrixXd R = m.topRightCorner(2, 1);
    cout << R << endl;
    return 0;
}