class Solution {
public:
    int fib(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        vector<int> dp(n + 1 , 0);
        dp[1] = 1;
        for(int i = 2 ; i <= n ; i ++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};


class Solution {
public:
    int fib(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        // 压缩
        vector<int> dp(2 , 0);
        dp[1] = 1;
        for(int i = 2 ; i <= n ; i ++) {
            int c = dp[1];
            dp[1] = dp[1] + dp[0];
            dp[0] = c;
        }
        return dp[1];
    }
};