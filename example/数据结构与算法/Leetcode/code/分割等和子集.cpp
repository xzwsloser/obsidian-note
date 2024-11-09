class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(auto& i : nums) sum += i;
        if(sum % 2 == 1) return false;
        int n = sum / 2;
        vector<int> dp(n + 1 , 0);
        for(int i = 0 ; i < nums.size() ; i ++) {
            for(int j = n ; j >= nums[i] ; j --) {
                dp[j] = max(dp[j] , dp[j - nums[i]] + nums[i]);
            }
        }
        return dp[n] == n;
    }
};