// 动态规划法
class Solution {
public:
    int countSubstrings(string s) {
        // dp[i][j] 表示范围为 [i,j] 之间的字符串是否为回文串
        // dp[i][j] = dp[i + 1][j - 1]
        vector<vector<bool>> dp(s.size() , vector<bool>(s.size() , false));
        int result = 0;
        for(int i = s.size() - 1 ; i >= 0 ; i --) {
            for(int j = i ; j < s.size() ; j ++) {
                if(s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    result ++;
                }
            }
        }
        return result;
    }
};

// 中心扩散法
class Solution {
public:
    int countSubstrings(string s) {
        int result = 0;
        for(int i = 0 ; i < s.size() ; i ++) {
            result += extend(s,i,i,s.size());
            result += extend(s,i,i + 1 , s.size());
        }
        return result;
    }
private:
    int extend(const string& s , int i , int j , int n) {
        int res = 0;
        while(i >= 0 && j < n && s[i] == s[j]) {
            i --;
            j ++;
            res ++;
        }
        return res;
    }
};