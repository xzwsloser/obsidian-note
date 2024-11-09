class Solution {
public:
    int numTrees(int n) {
        // 递推公式: 每一次把不同的节点当成头节点,比如利用 j 作为头节点
        // 那么左子树的节点个数就是 1 - j - 1 , 右边子树的节点个数就是 j + 1 - n 个
        // dp[i] += dp[j - 1] * dp[i - j];  1 <= j <= i
        vector<int> dp(n + 1 , 0);
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2 ; i <= n ; i ++) {
            for(int j = 1 ; j <= i ; j ++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }
        return dp[n];
    }
};