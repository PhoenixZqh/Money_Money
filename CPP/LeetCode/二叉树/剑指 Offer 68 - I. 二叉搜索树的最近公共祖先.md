```c++
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
         //递归第一步，终止条件
         if(root == NULL) return root;
         if(root->val > p->val && root->val > q->val)
         {
             TreeNode* left = lowestCommonAncestor(root->left, p, q);
             if(left != NULL) return left;
         }
         if(root->val < p->val && root->val < q->val)
         {
             TreeNode* right = lowestCommonAncestor(root->right,p,q);
             if(right != NULL) return right;
         }
         return root;
        
    }
};
```