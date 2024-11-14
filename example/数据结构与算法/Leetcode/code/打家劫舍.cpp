class Solution {
public:
    int rob(vector<int>& nums) {
        // dp[i] 表示索引为 0 - i 范围内的房屋被偷可以获得的最大收益
        // dp[i] = max(nums[i] + dp[i - 2] , dp[i - 1])
        if(nums.size() == 1) return nums[0];
        vector<int> dp(nums.size() , 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0] , nums[1]);
        for(int i = 2 ; i < nums.size() ; i ++) {
            dp[i] = max(dp[i - 1] , nums[i] + dp[i - 2]);
        }
        return dp[nums.size() - 1];
    }
};