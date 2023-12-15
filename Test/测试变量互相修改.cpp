#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    string res = "a b c d e";

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == 2 || nums[i] == 1)
        {
            for (size_t i = 0; i < res.size(); i++)
            {
                cout << "nums: " << nums[i] << endl;
                // cout << "resres[i] << endl;
            }
        }
    }

    return 0;
}