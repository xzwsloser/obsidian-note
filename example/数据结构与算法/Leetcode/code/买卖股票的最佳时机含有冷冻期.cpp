class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 状态的分布如下:
        // 不持有股票并且当天不卖出  --> 0
        // 不持有股票并且当天卖出    --> 1
        // 不持有股票并且处于冷冻期  --> 2
        // 持有股票               --> 3
        // dp[i][0] = max(dp[i - 1][0] , dp[i - 1][2])
        // dp[i][1] = dp[i - 1][3] + prices[i]
        // dp[i][2] = dp[i - 1][1]
        // dp[i][3] = max(dp[i - 1][0] - prices[i] , dp[i - 1][2] - prices[i])
        vector<vector<int>> dp(prices.size() , vector<int>(4,0));
        dp[0][0] = 0;
        dp[0][1] = 0;
        dp[0][2] = 0;
        dp[0][3] = -prices[0];
        for(int i = 1 ; i < prices.size() ; i ++) {
            dp[i][0] = max(dp[i - 1][0] , dp[i - 1][2]);
            dp[i][1] = dp[i - 1][3] + prices[i];
            dp[i][2] = dp[i - 1][1];
            dp[i][3] = max(dp[i - 1][3] , max(dp[i - 1][0] , dp[i - 1][2]) - prices[i]);
        }
        return max(dp[prices.size() - 1][0] , max(dp[prices.size() - 1][1] , dp[prices.size() - 1][2]));
    }
};