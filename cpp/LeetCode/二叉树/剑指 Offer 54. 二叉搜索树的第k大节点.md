二叉搜索树一般都与中序联系在一起，生成的是有序数组；


```c++
class Solution {
public:
    void midSort(TreeNode* root, vector<int> &res)
    {
        if(root == NULL) return;
        midSort(root->left,res);
        res.push_back(root->val);
        midSort(root->right,res);
    }
    int kthLargest(TreeNode* root, int k) {
        vector<int> res;
        midSort(root,res);
        return res[res.size()-k];
    }
};
```
