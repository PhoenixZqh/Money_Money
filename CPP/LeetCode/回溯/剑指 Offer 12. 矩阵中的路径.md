回溯
	1. 终止条件是超出边界或者不等于要满足的字母
	2. 满足条件是k已经到了word的最后一位，说明有这样的一条路径
	3. 后面就是向上下左右遍历，有一条路径满足则满足


```c++
class Solution {
public:
    bool dfs(vector<vector<char>>& board,int i, int j, int k, string word)
    {   
        int m = board.size();
        int n = board[0].size();
        //剪枝
        if(i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[k]) return false;
        if(k == word.size()-1) return true;
        board[i][j] = '\0';   //此格备用标记
        bool res = dfs(board, i-1, j, k+1, word) || dfs(board,i+1,j,k+1, word) || dfs(board,i,j-1,k+1,word) || dfs(board,i,j+1,k+1,word);
        board[i][j] = word[k];
        return res;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        for(int i=0;i<m;i++)
        {
            for(int j =0;j<n;j++)
            {
                if(dfs(board,i,j,0,word)) return true;
            }
        }
        
        return false;
    }
};
```