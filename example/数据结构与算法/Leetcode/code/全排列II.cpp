class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> used(nums.size() , false);
        sort(nums.begin() , nums.end());
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
            if(used[i]) continue;  // 使用过去重
            if(i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;  // 同一个树层中去重
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums , used);
            used[i] = false;
            path.pop_back();
        }
    }
};