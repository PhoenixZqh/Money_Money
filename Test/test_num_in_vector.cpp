#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> arr{1, 3, 5, 7, 9};
    int target;
    std::cout << "请输入: " << std::endl;
    std::cin >> target;

    bool in_vector = std::any_of(arr.begin(), arr.end(), [target](int num) {
        return num == target;
    });

    if (in_vector)
    {
        std::cout << "in vector" << std::endl;
    }
    else
    {
        std::cout << "not in vector " << std::endl;
    }

    return 0;
}