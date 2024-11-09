class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        // 剩下的容量最小也就是减去的容量最大
        // x+y --> y -x  --> 减少了 2*x
        // 定义背包容量为 sum / 2 即可
        int sum = 0;
        for(auto& i : stones) sum += i;
        int n = sum / 2;
        vector<int> dp(n + 1 , 0);
        for(int i = 0 ; i < stones.size() ; i ++) {
            for(int j = n ; j >= stones[i] ; j --) {
                dp[j] = max(dp[j] , dp[j - stones[i]] + stones[i]);
            }
        }
        return sum - 2*dp[n];
    }
};