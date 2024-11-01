class Solution {
public:
    vector<vector<int>> res;   // 存放最终结果
    vector<int> path;  // 路径
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size() , false);  // 用于记录是否使用过某一个元素
        backtracking(nums , used);
        return res;
    }
private:
    void backtracking(vector<int>& nums , vector<bool>& used) {
        if(path.size() == nums.size()) {
            res.push_back(path);
            return ;
        }
        for(int i = 0 ; i < nums.size() ; i ++) {
            if(used[i]) continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums , used);
            used[i] = false;
            path.pop_back();
        }
    }
};