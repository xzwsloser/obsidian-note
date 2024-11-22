class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<bool>> dp(s.size() + 1 , vector<bool>(t.size() + 1 , false));
        // if(s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1]
        // else  dp[i][j] = dp[i][j - 1]
        for(int i = 0 ; i <= t.size() ; i ++) {
            dp[0][i] = true;
        }
        for(int i = 1 ; i <= s.size() ; i ++) {
            for(int j = 1 ; j <= t.size() ; j ++) {
                if(s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp[s.size()][t.size()];
    }
};