/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 这里需要不断搜索 p 和 q 的位置
        if(root == q || root == p || root == nullptr) return root;
        TreeNode* left = lowestCommonAncestor(root -> left , p , q);
        TreeNode* right = lowestCommonAncestor(root -> right , p , q);
        // 此时一个在左子树,一个在右子树
        if(left != nullptr && right != nullptr) return root;
        else if(left != nullptr && right == nullptr) return left;
        else return right;
    }
};