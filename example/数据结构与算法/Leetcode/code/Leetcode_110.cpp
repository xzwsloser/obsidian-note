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
    int maxDepth(TreeNode* root) {
        // 后序遍历实现
        stack<TreeNode*> st;
        TreeNode* node;
        if(root != nullptr) st.push(root);
        int depth = 0 , result = 0;
        while(!st.empty()) {
            node = st.top();
            if(node != nullptr) {
                st.pop();
                st.push(node);
                st.push(nullptr);
                depth ++;  // 深入一层
                if(node -> right) st.push(node -> right);
                if(node -> left) st.push(node -> left);
            } else {
                st.pop();
                depth --;  // 回溯
                st.pop();
            }
            result = max(result , depth);
        }
        return result;
    }
};
