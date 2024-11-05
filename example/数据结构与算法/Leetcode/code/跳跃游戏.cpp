class Solution {
public:
    bool canJump(vector<int>& nums) {
        if(nums.size() == 1) return true;
        if(nums[0] == 0) return false;
        int startIndex = 0;
        int endIndex = 0;
        while(endIndex < nums.size()) {
            int maxIndex = endIndex;
            for(int i = startIndex ; i <= endIndex ; i ++) {
                if(i + nums[i] >= nums.size() - 1) return true;
                maxIndex = max(maxIndex , i + nums[i]);
            }
            startIndex = endIndex + 1;
            endIndex = maxIndex;
            if(startIndex > endIndex) return false;
            if(startIndex == endIndex && nums[endIndex] == 0) return false;
        }
        return  false;
    }
    
};



class Solution1 {
public:
    bool canJump(vector<int>& nums) {
        int cover = 0;  // 最大索引位置
        if(nums.size() == 0) return true;
        for(int i = 0 ; i <= cover ; i ++) {
            cover = max(cover , i + nums[i]);
            if(cover >= nums.size() - 1) return true;
        }
        return false;
    }
};