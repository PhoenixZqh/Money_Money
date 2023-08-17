输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。

```c++
class Solution {
public:
    string minNumber(vector<int>& nums) {
        string res;
        vector<string> str;
        for(int i=0;i<nums.size();i++)
        {
            str.push_back(to_string(nums[i]));
        }
        // sort(strs.begin(), strs.end(), [](string& s1, string& s2){return s1 + s2 < s2 + s1;});

        sort(str.begin(),str.end(), [](string &s1, string &s2)
        {
            return s1+s2 < s2 + s1;
        });
        for(auto s : str)
        {
            res.append(s);
        }
        return res;
    }
};
```
