// 动态规划
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        vector<int> dp(nums.size() , 1);
        int result = 1;
        for(int i = 1 ; i < nums.size() ; i ++) {
            dp[i] = nums[i] > nums[i - 1] ? dp[i - 1] + 1 : 1;
            result = max(result , dp[i]);
        }
        return result;
    }
};

// 贪心算法
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int result = 1;
        int counter = 1;
        for(int i = 1 ; i < nums.size() ; i ++) {
            if(nums[i] > nums[i - 1]) counter ++;
            else counter = 1;
            result = max(result , counter);
        }
        return result;
    }
};