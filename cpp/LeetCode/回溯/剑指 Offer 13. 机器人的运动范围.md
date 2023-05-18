回溯

1. 终止条件是超出边界，或者已经走过的格子或者坐标值大于k
2. 满足条件是向右向下遍历累加，找到一共有多少个格子


```c++
class Solution {
public:
    int getNum(int x
    {
        int res = 0;
        while(x)
        {
            res += x % 10;
            x /= 10;
        }
        return res;
    }
    int dfs(int i , int j, int m, int n, int k, vector<vector<bool>> &used)
    {
        if(i >= m || j >= n || getNum(i)+getNum(j)>k ||used[i][j] == true) return 0;
        used[i][j] = true;
        return 1 + dfs(i+1,j,m,n,k,used) + dfs(i,j+1,m,n,k,used);
    }
    int movingCount(int m, int n, int k) {
        vector<vector<bool>> used(m,vector<bool>(n,0));
        return dfs(0,0,m,n,k,used);
    }
};
```