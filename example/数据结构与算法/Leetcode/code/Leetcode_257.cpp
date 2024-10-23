class Solution {
public:
    vector<TreeNode*> path;
    vector<string> res;
    vector<string> binaryTreePaths(TreeNode* root) {
        if(root == nullptr) return res;
        path.push_back(root);
        travelsal(root);
        return res;
    }
private:
    void travelsal(TreeNode* root) {
        if(root -> left == nullptr && root -> right == nullptr) {
            int n = path.size();
            string s;
            for(int i = 0 ; i < n - 1 ; i ++) {
                s += to_string(path[i] ->  val);
                s += "->";
            }
            s += to_string(path[n - 1] -> val);
            res.push_back(s);
            return ;
        }

        if(root -> left != nullptr) {
            path.push_back(root -> left);
            travelsal(root -> left);
            path.pop_back();
        }

        if(root -> right != nullptr) {
            path.push_back(root -> right);
            travelsal(root -> right);
            path.pop_back();
        }
    }
};