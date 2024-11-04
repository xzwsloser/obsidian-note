class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if(nums.size() == 1) return 1;
        int preDiff = 0;
        int curDiff = 0;
        int result = 1;   // 默认最左边有一个峰值
        for(int i = 0 ; i < nums.size() - 1 ; i ++) {
            curDiff = nums[i + 1] - nums[i];
            if((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
                result ++;
                preDiff = curDiff;
            }
        }
        return result;
    }
};