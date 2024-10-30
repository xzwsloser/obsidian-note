class Solution {
public:
    vector<vector<int>> res;  /* 最终需要返回的结果 */
    vector<int> path;  /* 路径 */
    int sum = 0;  /* 总和 */
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        res.clear();
        path.clear();
        backtracking(candidates , target , 0);
        return res;
    }

private:
    void backtracking(vector<int>& candidates , int target , int startIndex) {
        if(sum > target) return;
        if(sum == target) {
            res.push_back(path);
            return ;
        }
        for(int i = startIndex ; i < candidates.size() ; i ++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            backtracking(candidates , target , i);
            sum -= candidates[i];
            path.pop_back();
        }
    }
};