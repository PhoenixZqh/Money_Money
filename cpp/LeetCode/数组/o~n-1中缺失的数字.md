这道题最开始我的想法是将存在的所有情况考虑进来；
简单的做法是二分查找，因为这个数组是递增的；

```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {

        int l=0, r = nums.size()-1;
        while(l < r)
        {
            int mid = (r - l)/2 + l;
            if(nums[mid] == mid) l = mid+1;
            if(nums[mid] != mid) r = mid;
        }
        return l;
    }
};
```

