/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        // 1. 如果当前节点 root -> val < low , 那么就需要删除左边的左右节点
        // 2. 如果当前节点 root -> val > hign , 那么就需要删除右边的所有节点
        // 3. 如果当前满足条件继续递归
        if(root == nullptr) return root;
        if(root -> val < low) {
            return trimBST(root -> right , low , high);
        }
        if(root -> val > high) {
            return trimBST(root -> left , low , high);
        }

        if(root -> val >= low && root -> val <= high) {
            root -> left = trimBST(root -> left , low , high);
            root -> right = trimBST(root -> right , low , high);
            return root;
        }
        return root;
    }
};