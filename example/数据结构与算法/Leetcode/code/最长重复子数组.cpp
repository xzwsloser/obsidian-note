class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        // dp[i][j] 表示长度为 i 的 nums1 的字符串和 长度为 j 的字符串的公共子串
        vector<vector<int>> dp(nums1.size() + 1 , vector<int>(nums2.size() + 1 , 0));
        int result = 0;
        for(int i = 1 ; i <= nums1.size() ; i ++) {
            for(int j = 1 ; j <= nums2.size() ; j ++) {
                if(nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                result = max(result,dp[i][j]);
            }
        }
        return result;
    }
};

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        vector<int> dp(nums2.size() + 1 , 0);
        int result = 0;
        for(int i = 1 ; i <= nums1.size() ; i ++) {
            for(int j = nums2.size() ; j > 0 ; j --) {
                if(nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                } else {
                    dp[j] = 0;
                }
                result = max(result,dp[j]);
            }
        } 
        return result;
    }
};