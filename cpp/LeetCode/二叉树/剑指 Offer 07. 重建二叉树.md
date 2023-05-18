```c++
class Solution {
public:
    TreeNode* dfs(vector<int>& preorder,int prebegin,int preend,vector<int>& inorder,int inbegin,int inend)
    {
        if(preend == prebegin) return NULL;
        int val = preorder[prebegin];
        TreeNode *root = new TreeNode(val);
        if(preend - prebegin == 1) return root;
        int i;
        for(i=inbegin;i<inend;i++)
        {
            if(inorder[i] == val)
            {
                break;
            }
        } 
        int left_inbegin = inbegin;
        int left_inend = i;
        int right_inbegin = i+1;
        int right_inend = inend;
        
        int left_prebegin = prebegin+1;
        int left_preend = prebegin+i+1-inbegin;
        int right_prebegin = prebegin+i+1-inbegin;
        int right_preend = preend;
        root->left = dfs(preorder,left_prebegin,left_preend,inorder,left_inbegin,left_inend);
        root->right = dfs(preorder,right_prebegin,right_preend,inorder,right_inbegin,right_inend);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.size() == 0 ||inorder.size() == 0) return NULL;
        return dfs(preorder,0,preorder.size(),inorder,0,inorder.size());
    }
};
```