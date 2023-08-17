啥意思呢？

	1. 如果绳子长度在3以内，是不是怎么剪最大长度都为i-1；
	2. 动规数组的初始化，代表的是我剪下来的绳子的长度，比如说绳子原长6，剪下来2，那么就用这个2去乘，而不是1；
	3. 内层循环为什么到外层的一般就结束了？因为你剪掉4和你剪掉2的效果是一样的
最后这个乘积就是dp[j] * dp[i-j]

```c++
class Solution {
public:
    int cuttingRope(int n) {
        
        //写在最前面，相当于剪枝
        if(n <=3) return n-1;
        //创建dp数组 
        vector<int> dp(n+1,0);
 
        //dp[i]代表的是长度为i的绳子的最大乘积
        //初始化
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;
        
        //递推表达式
        for(int i=4;i<=n;i++)
        {
            for(int j=1;j<=i/2;j++)
            {
                dp[i] = max(dp[i] , dp[j]*dp[i-j]);
            }
        }
        return dp[n];
    }
};
```