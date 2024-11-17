class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        // 假设卖出的时候交上手续费
        // 0  --> 不持有股票
        // 1  --> 持有股票
        // dp[i][0] = max(dp[i - 1][0] , dp[i - 1][1] + prices[i] - fee)
        // dp[i][1] = max(dp[i - 1][1] , dp[i - 1][0] - prices[i])
        vector<vector<int>> dp(prices.size() , vector<int>(2,0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for(int i = 1 ; i < prices.size() ; i ++) {
            dp[i][0] = max(dp[i - 1][0] , dp[i - 1][1] + prices[i] - fee);
            dp[i][1] = max(dp[i - 1][1] , dp[i - 1][0] - prices[i]);
        }
        return dp[prices.size() - 1][0];
    }
};