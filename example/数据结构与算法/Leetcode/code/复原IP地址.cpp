class Solution {
public:
    vector<string> res;  /* 记录最终结果 */
    vector<string> restoreIpAddresses(string s) {
        if(s.size() < 4 || s.size() > 12) return res;
        backtracking(s , 0 , 0);
        return res;
    }
private:
    void backtracking(string& s , int startIndex , int pointNum) {
        if(pointNum == 3) {
            if(isVaild(s , startIndex , s.size() - 1)) {
                res.push_back(s);
            }
            return ;
        }
        for(int i = startIndex ; i < s.size() ; i ++) {
            if(!isVaild(s , startIndex , i)) break;  // 这类直接结束了,继续分割就会更大
            s.insert(s.begin() + i + 1 , '.');
            pointNum++;
            backtracking(s , i + 2 , pointNum);
            pointNum--;
            s.erase(s.begin() + i + 1);  // 回溯
        }
    }
    bool isVaild(const string& s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s[start] == '0' && start != end) { // 0开头的数字不合法
                return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }
};