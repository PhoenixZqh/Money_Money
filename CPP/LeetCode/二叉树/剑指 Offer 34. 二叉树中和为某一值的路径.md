```c++
class Solution {
    vector<int>path;
    vector<vector<int> > res;
public:
    void dfs(TreeNode* root, int target)
    {
        if(root == nullptr) return;
        if(target ==0 && root->left==nullptr && root->right==nullptr)
        {
            res.push_back(path);
        }
        target-= root->val;
        path.push_back(root->val);
        
        pathSum(root->left,target);
        pathSum(root->right, target);
        path.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        
        
        dfs(root,target);
        return res;
    }
};
```