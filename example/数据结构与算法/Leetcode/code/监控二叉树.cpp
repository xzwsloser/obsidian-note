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
    int result ;
    int minCameraCover(TreeNode* root) {
        if(root == nullptr) return 0;
        if(root -> left == nullptr && root -> right == nullptr) return 1;
        result = 0;
        if(backtracking(root) == 0) result ++;  // 表示根节点没有覆盖
        return result;
    }
private:
    // 状态:
    /**
        0    ---> nullptr    ---> 与  2 合并
        1    ---> 没有被监控
        2    ---> 被监控但是没有摄像头  与 0 合并
        3    ---> 安装了摄像头

        0 ---> 节点没有被覆盖
        1 ---> 节点有摄像头
        2 ---> 节点被覆盖
    */
    int backtracking(TreeNode* root) {
        if(root == nullptr) return 2;
        int left = backtracking(root -> left);
        int right = backtracking(root -> right);
        // 只要有一个没有覆盖就需要摄像头
        if(left == 0 || right == 0) {
            result ++;
            return 1;
        } else if(left == 1 || right == 1) {
            return 2;
        } else if(left == 2 && right == 2) {
            return 0;
        }
        return 2;
    }
};