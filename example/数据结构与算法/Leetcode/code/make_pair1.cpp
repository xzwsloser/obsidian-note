class Solution {
public:
    vector<vector<int>> res;  // 存放结果
    vector<int> path;  // 存放路径
    vector<vector<int>> combine(int n, int k) {
        res.clear();
        path.clear();
        backtraking(1 , n , k);
        return res;
    }
private:
    void backtraking(int index , int n , int k) {
        if(path.size() == k) {
            res.push_back(path);
            return ;
        }

        for(int i = index ; i <= n ; i ++) {
            path.push_back(i);
            backtraking(i + 1 , n , k);
            path.pop_back();
        }
    }
};