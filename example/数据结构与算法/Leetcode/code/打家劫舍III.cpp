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
    int rob(TreeNode* root) {
        if(root == nullptr) return 0;
        vector<int> result = getMaxValue(root);
        return max(result[0] , result[1]);
    }
public:
    vector<int> getMaxValue(TreeNode* root) {
        if(root == nullptr) return vector<int>(2, 0);
        if(root -> left == nullptr && root -> right == nullptr) return vector<int>({root -> val , 0});
        vector<int> left = getMaxValue(root -> left);
        vector<int> right = getMaxValue(root -> right);
        return vector<int>({root -> val + left[1] + right[1] , max(left[0] , left[1]) + max(right[0] , right[1])});
    }
};