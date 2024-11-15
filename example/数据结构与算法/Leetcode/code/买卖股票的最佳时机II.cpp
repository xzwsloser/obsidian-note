// 动态规划
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // dp[i][0] 表示第 i 天不持有股票的最大利润
        // dp[i][1] 表示第 i 天持有股票的最大利润
        // dp[i][0] = max(dp[i - 1][0] , dp[i - 1][1] + prices[i])
        // dp[i][1] = max(dp[i - 1][1] , dp[i - 1][0] - prices[i])
        vector<vector<int>> dp(prices.size() , vector<int>(2, 0));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for(int i = 1 ; i < prices.size() ; i ++) {
            dp[i][0] = max(dp[i - 1][0] , dp[i - 1][1] + prices[i]);
            dp[i][1] = max(dp[i - 1][1] , dp[i - 1][0] - prices[i]);
        }
        return dp[prices.size() - 1][0];
    }
};

// 贪心算法
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        for(int i = 0 ; i < prices.size() - 1 ; i ++) {
            result += max(0 , prices[i + 1] - prices[i]);
        }
        return result;
    }
};