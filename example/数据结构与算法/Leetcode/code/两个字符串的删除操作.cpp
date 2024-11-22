class Solution {
public:
    int minDistance(string word1, string word2) {
        // dp[i][j] 表示长度为 i 的子字符串 word1 和长度为 j 的子字符串 word2 需要的变换的最小次数
        // if(word1[i - 1] == word2[j - 1]) dp[i][j] = dp[i - 1][j - 1]
        // else       dp[i][j] = min(dp[i - 1][j] , dp[i][j - 1] , 2 + dp[i - 1][j - 1]) 
        // dp[0][i] = i dp[j][0] = j
        vector<vector<int>> dp(word1.size() + 1 , vector<int>(word2.size() + 1 , 0));
        for(int i = 0 ; i <= word1.size() ; i ++) dp[i][0] = i;
        for(int j = 0 ; j <= word2.size() ; j ++) dp[0][j] = j;
        for(int i = 1 ; i <= word1.size() ; i ++) {
            for(int j = 1 ; j <= word2.size() ; j ++) {
                if(word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min(min(dp[i - 1][j] , dp[i][j - 1]) + 1 , dp[i - 1][j - 1] + 2);  // min(dp[i - 1][j] , dp[i][j - 1]) + 1
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};