从若干副扑克牌中随机抽 5 张牌，判断是不是一个顺子，即这5张牌是不是连续的。2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。A 不能视为 14。


```c++
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        int zeroes = 0;
        sort(nums.begin(),nums.end());
        for(int i=0;i<4;i++)
        {
            if(nums[i] == 0) 
            {
                zeroes++;
                continue;
            }
            if(nums[i] == nums[i+1]) return false;
            zeroes -= nums[i+1] - nums[i] - 1;
        }
        return zeroes>=0;
    }
};

```