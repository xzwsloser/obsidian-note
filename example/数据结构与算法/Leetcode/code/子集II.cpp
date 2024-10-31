class Solution {
public: 
    vector<int> path;  /* 路径 */
    vector<vector<int>> res;  /* 结果 */
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        // 元素重复但是要求结果不重复需要利用数组进行去重操作
        sort(nums.begin() , nums.end());
        vector<bool> used(nums.size() , false);
        backtracking(used , nums , 0);
        return res;
    }
private:
    void backtracking(vector<bool>& used , vector<int>& nums , int startIndex) {
        res.push_back(path);
        for(int i = startIndex ; i < nums.size() ; i ++) {
            // 去重复操作 类似于三数之和(三指针)
            if(i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(used , nums , i + 1);
            used[i] = false;
            path.pop_back();
        }
    }
};