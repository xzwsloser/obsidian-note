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
    bool hasPathSum(TreeNode* root, int targetSum) {
        // 包含当前节点   
        if(root == nullptr) return false;
        sum += root -> val;
        return pathSum(root , targetSum);
    }
private:
    bool pathSum(TreeNode* root , int targetSum) {
        if((root -> left == nullptr && root -> right == nullptr) && sum == targetSum) return true;

        if(root -> left) {
            sum += root -> left -> val;
            if(pathSum(root -> left , targetSum)) return true;
            sum -= root -> left -> val;
        }

        if(root -> right) {
            sum += root -> right -> val;
            if(pathSum(root -> right , targetSum)) return true;
            sum -= root -> right -> val;
        }
        return false;
    }
};