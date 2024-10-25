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
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        // 使用层序遍历
        if(root1 == nullptr) return root2;
        if(root2 == nullptr) return root1;
        queue<TreeNode*> que;
        que.push(root1);
        que.push(root2);
        TreeNode* node1;
        TreeNode* node2;
        while(!que.empty()) {
            node1 = que.front();
            que.pop();
            node2 = que.front();
            que.pop();
            node1 -> val += node2 -> val;
            if(node1 -> left != nullptr && node2 -> left != nullptr) {
                que.push(node1 -> left);
                que.push(node2 -> left);
            }

            if(node1 -> right != nullptr && node2 -> right != nullptr) {
                que.push(node1 -> right);
                que.push(node2 -> right);
            }

            if(node1 -> left == nullptr && node2 -> left != nullptr) {
                node1 -> left = node2 -> left;  // 直接替换了
            }

            if(node1 -> right == nullptr && node2 -> right != nullptr) {
                node1 -> right = node2  -> right;
            }
        }
        return root1;
    }
    
};