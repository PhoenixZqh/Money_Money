#include <chrono>
#include <iostream>
#include <vector>

/**
 * @brief 测试两层for循环耗时
 */

using namespace std;

vector<vector<int>> testArray(4000, vector<int>(4000));

void TestForloopTime()
{
    for (int i = 0; i < testArray.size(); i++)
    {
        for (int j = 0; j < testArray[0].size(); j++)
        {
            testArray[i][j] = i * j + 5;
        }
    }
}

int main()
{
    auto start_time = std::chrono::high_resolution_clock::now();
    TestForloopTime();
    auto end_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;
}