class Solution {
public:
    int change(int amount, vector<int>& coins) {
        // dp[j] 表示目标为 j 的时候,组合的最大数量
        // 递推公式: dp[j] += dp[j - nums[i]]
        vector<uint64_t> dp(amount + 1 , 0);
        dp[0] = 1;
        for(int i = 0 ; i < coins.size() ; i ++) {
            for(int j = coins[i] ; j <= amount ; j ++) {
                dp[j] += dp[j - coins[i]];
            }
        }
        return (int)dp[amount];
    }
};