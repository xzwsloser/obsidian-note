class Solution {
public:
    vector<vector<int>> res;  /* 用于记录最终的结果 */
    vector<int> path;    /* 路径 */
    int sum;  /* 总和 */
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<bool> used(candidates.size() , false);  /* 表示元素是否正在被使用 */
        sort(candidates.begin() , candidates.end());
        backtracking(candidates , used , target , 0);
        return res;
    }
private:
    void backtracking(vector<int>&candidates , vector<bool>& used , int target , int startIndex) {
        if(sum > target) return;
        if(sum == target) {
            res.push_back(path);
            return ;
        }
        for(int i = startIndex ; i < candidates.size() ; i ++) {
            if(sum + candidates[i] > target) return ; /* 这一个数层不用遍历了 */
            if(i > 0 && candidates[i] == candidates[i - 1] && !used[i - 1]) continue;  /*  表示同一个树层中,跳过 */
            sum += candidates[i];
            path.push_back(candidates[i]);
            used[i] = true;  /* 表示当前元素正在使用 */
            backtracking(candidates , used , target , i + 1);
            used[i] = false;  /* 当前元素没有使用 */
            sum -= candidates[i];
            path.pop_back();
        }
    }
};