```c++
class Solution {
public:
    bool dfs(int l,int r, vector<int>& res)
    {
        //递归的返回条件
        if(l >= r) return true;
        int root = res[r];
        int k = l;
        while(k < r && res[k] < root) k++;
        for(int i = k;i<r;i++)
        {
            if(res[i] < root) return false;
        }
        
        return dfs(l,k-1,res) && dfs(k,r-1,res);
    }
    
    bool verifyPostorder(vector<int>& postorder) {
        return dfs(0,postorder.size()-1,postorder);
    }
};
```