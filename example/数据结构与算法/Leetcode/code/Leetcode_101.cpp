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
    bool isSymmetric(TreeNode* root) {
        // 利用迭代法
        if(root == nullptr) return true;
        queue<TreeNode*> que;
        que.push(root -> left);
        que.push(root -> right);
        while(!que.empty()) {
            TreeNode* rightNode = que.front();
            que.pop();
            TreeNode* leftNode = que.front();
            que.pop();
            if(!rightNode && !leftNode) continue;

            if(!rightNode || !leftNode || (rightNode -> val != leftNode -> val)) return false;

            que.push(leftNode -> left);
            que.push(rightNode -> right);
            que.push(leftNode -> right);
            que.push(rightNode -> left);
        }
        return true;
    }
};