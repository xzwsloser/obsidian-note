class Solution {
public:
    static bool cmp(int& a , int& b) {
        return abs(a) > abs(b);
    }
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin() , nums.end() , cmp); 
        for(int i = 0 ; i < nums.size() ; i ++) {
            if(nums[i] < 0 && k > 0) {
                nums[i] *= (-1);
                k --;
            }
        }
        if(k % 2 == 1) nums[nums.size() - 1] *= (-1);
        int sum = 0;
        for(int& i : nums) sum += i;
        return sum;
    }
};




// 或者在遍历的过程中找到需要改变的元素

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        int sum = 0;
        int minVal = INT_MAX;
        for (auto& val : A) {
            if (val < 0 && K > 0) {
                K--;
                val = -val;
            }
            sum += val;
            minVal = min(minVal, val);  // 记录最小值
        }
        if (K > 0 && (K & 1)) { // K还有剩余次数，且为奇数次(偶数次反转后还是正数，不需要考虑)
            sum = sum - 2 * minVal;    // 减去2倍的最小值 
        }
        return sum;
    }
};

