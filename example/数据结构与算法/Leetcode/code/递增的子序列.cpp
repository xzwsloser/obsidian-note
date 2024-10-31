class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtracking(nums , 0);
        return res;
    }
private:
    void backtracking(vector<int>& nums , int startIndex) {
        if(path.size() > 1) res.push_back(path);
        unordered_set<int> uset;
        for(int i = startIndex ; i < nums.size() ; i ++) {
            // 找到合适的位置
            if(!path.empty() && nums[i] < path.back() || uset.find(nums[i]) != uset.end()) continue;
            path.push_back(nums[i]);
            uset.insert(nums[i]);
            backtracking(nums , i + 1);
            path.pop_back();
        }
    }
};