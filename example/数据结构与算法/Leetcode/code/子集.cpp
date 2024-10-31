class Solution {
public:
    vector<vector<int>> res;  /* 存储最终结果 */
    vector<int> path;  /* 存储遍历路径 */
    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums , 0);
        return res;
    }
private:
    // 只用在回溯函数前面加上收集节点的操作即可
    void backtracking(vector<int>& nums , int startIndex) {
        res.push_back(path);
        for(int i = startIndex ; i < nums.size() ; i ++) {
            path.push_back(nums[i]);
            backtracking(nums , i + 1);
            path.pop_back();
        }
    }
};