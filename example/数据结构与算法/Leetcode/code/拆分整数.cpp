class Solution {
public:
    int integerBreak(int n) {
        // 思路: dp[n]  表示和的乘积的最大值
        // 递推公式: dp[i] = max(dp[i - k] * dp[k] , dp[k] * (i - k))
        vector<int> dp(n + 1 , 0);
        dp[2] = 1;
        for(int i = 3 ; i <= n ; i ++) {
            for(int k = 1 ; k <= (i / 2)  ; k ++) {
               dp[i] = max(dp[i] , max((i - k) * k , dp[i - k] * k));
            }
        }
        return dp[n];
    }
};



// 贪心算法 + 均值不等式

class Solution {
public:
    int integerBreak(int n) {
        if (n == 2) return 1;
        if (n == 3) return 2;
        if (n == 4) return 4;
        int result = 1;
        while (n > 4) {
            result *= 3;
            n -= 3;
        }
        result *= n;
        return result;
    }
};