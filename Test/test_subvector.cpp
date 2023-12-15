#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool containsAllSubstrings(const std::string &target, const std::vector<std::string> &substrings)
{
    for (const auto &substring : substrings)
    {
        if (target.find(substring) == std::string::npos)
        {
            return false; // 未找到子串，不包含所有子串
        }
    }
    return true; // 所有子串都找到，包含所有子串
}

int main()
{
    std::string targetString = "bdu gun back people";
    std::vector<std::string> substrings = {"bdu", "gun", "aaa"};

    if (containsAllSubstrings(targetString, substrings))
    {
        std::cout << "yes" << std::endl;
    }
    else
    {
        std::cout << "no" << std::endl;
    }

    return 0;

    // std::vector<std::string> all_cls = {"gun", "bdu", "backpack", "people"};

    // std::vector<std::string> cls = {"gun", "bdu", "aaa"};

    // bool isSubset = std::includes(all_cls.begin(), all_cls.end(), cls.begin(), cls.end());

    // std::cout << isSubset << std::endl;

    // std::string str_ = "gun bdu backpack people";
    // std::string str1 = "people gun";
    // size_t found = str_.find(str1);

    // if (found != std::string::npos)
    // {
    //     std::cout << "yes!" << std::endl;
    // }
    // else
    // {
    //     std::cout << "no" << std::endl;
    // }

    vector<string> res;

    res.push_back("");
    res.push_back("gun");
    res.push_back("back");

    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }
    return 0;
}