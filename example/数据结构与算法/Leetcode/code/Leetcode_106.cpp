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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return backtracking(inorder , postorder , 0 , inorder.size() - 1, 0 , postorder.size() - 1);
    }
private:
    TreeNode* backtracking(vector<int>& inorder , vector<int>& postorder , int ib , int ie , int pb , int pe) {
        // 1. 确定终止条件
        if((ie < ib) || (pe < pb)) return nullptr;
        // 2. 确定单层递归逻辑
        TreeNode* root = new TreeNode(postorder[pe]);
        // 找到左子树和右子树的位置
        int i;
        for(i = 0 ; i < inorder.size() ; i ++) {
            if(inorder[i] == postorder[pe]) break; 
        }
        // 所以对于左子树   ib - (i - 1)   pb - pb + i - 1 - ib
        // 对于右子树      (i + 1) - ie    (pe + i - ie) - pe - 1       pe - 1 - x = ie - i - 1 ==> x == pe - 1 + i + 1 - ie  
        root -> left = backtracking(inorder , postorder , ib , i - 1 , pb , pb + i - 1 - ib);
        root -> right = backtracking(inorder , postorder , i + 1 , ie , pe + i - ie , pe - 1);
        return root;
    }
};