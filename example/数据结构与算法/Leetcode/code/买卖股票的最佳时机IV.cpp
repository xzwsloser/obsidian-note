class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        vector<vector<int>> dp(prices.size() , vector<int>(2*k + 1 , 0));
        for(int i = 0 ; i <= 2*k ; i ++) {
            dp[0][i] = i % 2 == 0 ? 0 : -prices[0];
        }
        for(int i = 1 ; i < prices.size() ; i ++) {
            dp[i][0] = dp[i - 1][0];
            for(int j = 1 ; j <= 2*k ; j ++) {
                dp[i][j] = j % 2 == 0 ? max(dp[i - 1][j] , dp[i - 1][j - 1] + prices[i]) : max(dp[i - 1][j] , dp[i - 1][j - 1] - prices[i]);
            }
        }
        return dp[prices.size() - 1][2*k];
    }
};