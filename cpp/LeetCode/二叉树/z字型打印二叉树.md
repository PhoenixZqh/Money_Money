把奇数行反转一下就行啊

```c++
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        
        vector<vector<int> > res;
        queue<TreeNode*> que;
        if(root != NULL) que.push(root);
        while(!que.empty())
        {
            vector<int> path;
            TreeNode* node;
            int size = que.size();
            while(size--)
            {
                node = que.front();
                que.pop();
                path.push_back(node->val);
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            res.push_back(path);
        }
        for(int i = 1;i<res.size();i+=2)
        {
            reverse(res[i].begin(),res[i].end());
        }
        return res;
    }
};
```
