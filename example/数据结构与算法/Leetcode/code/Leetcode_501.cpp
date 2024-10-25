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
    vector<int> result;
    TreeNode* pre = NULL; // 最好利用节点记录
    int maxCount = 0;
    int count = 0;
    vector<int> findMode(TreeNode* root) {
        result.clear();
        pre = NULL;
        maxCount = 0;
        count = 0;
        backtracking(root);
        return result;
    }
private:
    void backtracking(TreeNode* root) {
        if(root == nullptr) return ;
        backtracking(root -> left);  // 左
        if(pre == NULL) {
            count = 1;  // 第一个节点
        } else if(root -> val == pre -> val) {
            count ++;
        } else {
            count = 1;
        }
        pre = root;  // 根新第一个节点

        if(maxCount == count) {
            result.push_back(root -> val);
        }

        if(count > maxCount) {
            maxCount = count;
            result.clear();
            result.push_back(root -> val);
        }
        backtracking(root -> right);
      
    }
};