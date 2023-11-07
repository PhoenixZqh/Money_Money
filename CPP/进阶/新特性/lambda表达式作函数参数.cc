
/*
 * @Author: phoenixZ
 * @Date: 2023-11-07 16:27:34
 * @Last Modified by: phoenixZ
 * @Last Modified time: 2023-11-07 16:27:34
 * @Description: 
*/

/**
 * @brief 给定一个数组， 保留数组中比10大的数字；
*/

#include <iostream>
#include <vector>

using namespace std;

template <typename Function>
void DeleteNumInVec(vector<int> vec, Function func)
{
    func();
}

int main()
{
    vector<int> vec{10, 9, 2, 3, 12, 33, 1, 6, 4, 22};
    DeleteNumInVec(vec, [&]() {
        for (int i = vec.size() - 1; i >= 0; i--)
        {
            if (vec[i] > 10)
            {
                vec.erase(vec.begin() + i);
            }
        }
    });

    for (auto i : vec)
    {
        cout << i << "\t";
    }

    return 0;
}