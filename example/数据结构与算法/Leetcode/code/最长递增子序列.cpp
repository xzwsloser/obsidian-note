class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // dp[i] 表示以索引 i 结尾的最大元素值
        // dp[i] = dp[j] + 1 中的最大值
        vector<int> dp(nums.size() , 1);
        int result = 1;
        for(int i = 1 ; i < nums.size() ; i ++) {
            for(int j = 0 ; j < i ; j ++) {
                if(nums[i] > nums[j]) {
                    dp[i] = max(dp[i] , dp[j] + 1);
                }
            }
            result = max(result , dp[i]);
        }   
        return result;
    }
};