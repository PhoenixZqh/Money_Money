#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

void DeleteMaxMin(vector<float> &vec)
{
    for (auto i : vec)
    {
        cout << i << "\t";
    }

    cout << "\n"
         << endl;

    if (vec.size() < 2)
        cout << "vector's size is too small" << endl;

    auto minIdx = min_element(vec.begin(), vec.end());
    auto maxIdx = max_element(vec.begin(), vec.end());

    float tolerance = 0.0001;
    vec.erase(std::remove_if(vec.begin(), vec.end(), [=](float x) {
                  return std::abs(x - *maxIdx) < tolerance || std::abs(x - *minIdx) < tolerance;
              }),
              vec.end());

    for (auto i : vec)
    {
        cout << i << "\t";
    }

    cout << "\n"
         << endl;
}

int main()
{
    vector<float> test_vec{0.001, 2.3, 155.3, 3.2, 5.5, 6.5, 1.1, 8.7, 12.6, 0.09, 20.2, 11.1, 2.0};

    auto start_time = std::chrono::high_resolution_clock::now();
    DeleteMaxMin(test_vec);
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "代码块执行时间: " << duration.count() << " 微秒" << std::endl;

    return 0;
}