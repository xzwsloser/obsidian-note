class Solution {
public:
    vector<vector<string>> res;  /* 最终得到的答案 */
    vector<string> path;         /*  遍历路径 */
    vector<vector<string>> partition(string s) {
        backtracking(s , 0);
        return res;
    }
private:
    bool isSame(string& t , int begin , int end) {
        int i = begin;
        int j = end;
        while(i < j) {
            if(t[i] != t[j]) return false;
            i ++;
            j --;
        }
        return true;
    }
    // s 表示需要进行回溯操作的字符串,startIndex表示从当前字符串开始截取
    void backtracking(string& s , int startIndex) {
        if(startIndex == s.size()) {
            res.push_back(path);
            return ;
        }
        // 开始遍历操作
        for(int i = startIndex ; i < s.size() ; i ++) {
            // 此时需要截取 [startIndex , i]内字符串
            if(!isSame(s , startIndex , i)) continue;
            path.push_back(s.substr(startIndex , i - startIndex + 1));
            backtracking(s , i + 1);  // 从后面开始截取,如果已经包含最后一个字符串直接退出了
            path.pop_back();
        }
    }
};