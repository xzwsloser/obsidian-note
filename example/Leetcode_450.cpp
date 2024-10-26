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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root == nullptr) return root;
        if(root -> val == key) {
            // 删除 root
            TreeNode* left = root -> left;
            TreeNode* right = root -> right;
            if(left != nullptr && right != nullptr) {
                TreeNode* cur = right;
                while(cur -> left != nullptr) cur = cur -> left;
                cur -> left = left;
                return right;
            } else if(left != nullptr && right == nullptr) {
                return left;
            } else if(left == nullptr && right != nullptr) {
                return right;
            } else {
                return nullptr;
            }
          
        } 
        
        if(root -> val < key) {
            root -> right = deleteNode(root -> right , key);
        }

        if(root -> val > key) {
            root -> left = deleteNode(root -> left , key);
        }

        return root;
    }
};