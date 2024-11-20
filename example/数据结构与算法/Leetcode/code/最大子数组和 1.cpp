// // 动态规划
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // dp[j] 表示以 nums[j]结尾的连续数组的最大和
        // dp[j] = dp[j - 1] < 0 : nums[j] : dp[j - 1] + nums[j]
        int result = nums[0];
        vector<int> dp(nums.size() , 0);
        dp[0] = nums[0];
        for(int j = 1 ; j < nums.size() ; j ++) {
            dp[j] = dp[j - 1] < 0 ? nums[j] : dp[j - 1] + nums[j];
            result = max(result,dp[j]);
        }
        return result;
    }
};

// 贪心算法
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int result = nums[0];
        int count = nums[0];
        for(int i = 1 ; i < nums.size() ; i ++) {
            if(count < 0) {
                count = nums[i];
            } else {
                count += nums[i];
            }
            result = max(result,count);
        }
        return result;
    }
};