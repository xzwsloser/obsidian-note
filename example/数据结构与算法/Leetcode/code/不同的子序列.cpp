class Solution {
public:
    int numDistinct(string s, string t) {
        // dp[i][j] 表示长度为 i 的 s  和长度为 j 的t 之间的变化种类数量
        // if(s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1]
        // else  dp[i][j] = dp[i - 1][j]
        vector<vector<uint64_t>> dp(s.size() + 1 , vector<uint64_t>(t.size() + 1 , 0));
        for(int i = 0 ; i <= s.size() ; i ++) {
            dp[i][0] = 1;
        }
        for(int i = 1 ; i <= s.size() ; i ++) {
            for(int j = 1 ; j <= t.size() ; j ++) {
                if(s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[s.size()][t.size()];
    }
};