class Solution {
public:
    vector<int> path;  /* 路径 */
    vector<vector<int>> res;  /* 最终需要返回的结果 */
    int sum = 0;  /* 总和 */
    vector<vector<int>> combinationSum3(int k, int n) {
        path.clear();
        res.clear();
        sum = 0;
        backtracking(1 , k , n);
        return res;
    }
private:
    void backtracking(int startIndex , int k , int n) {
        if(sum == n && path.size() == k) {
            res.push_back(path);
            return ;
        }
        
        for(int i = startIndex ; i <= 9 - (k - path.size()) + 1 ; i ++) {
            if(sum + i > n) return ;
            path.push_back(i);
            sum += i;
            backtracking(i + 1 , k , n);
            path.pop_back();
            sum -= i;
        }
    }
};