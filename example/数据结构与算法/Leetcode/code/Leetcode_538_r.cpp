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
    int sum = 0;
    TreeNode* convertBST(TreeNode* root) {
        travelsal(root);
        return root;
    }
private:
    void travelsal(TreeNode* root) {
        if(root == nullptr) return ;
        travelsal(root -> right);
        sum += root -> val;
        root -> val = sum;
        travelsal(root -> left);
    }
};