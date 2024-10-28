class Solution {
public:
    vector<vector<int>> res;
    vector<int> path;
    vector<vector<int>> combine(int n, int k) {
        // 集合中的元素个数为 path.size()  还需要 k - path.size()
        // 所以如果从 index 开始遍历,得到的最多的整数个数为 n - index + 1 >= k - path.size();
        // index <= n + 1 - (k - path.size())
        backtracking(1 , n , k);
        return res;
    }
private:
    void backtracking(int startIndex , int n , int k) {
        if(path.size() == k) {
            res.push_back(path);
            return ;
        }

        for(int i = startIndex ; i <= n + 1 - (k - path.size()) ; i ++) {
            path.push_back(i);
            backtracking(i + 1 , n , k);
            path.pop_back();
        }
    }
};