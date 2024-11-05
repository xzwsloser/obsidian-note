class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> obtain(ratings.size() , 1);
        // 从前面向后面遍历
        for(int i = 1 ; i < ratings.size() ; i ++) {
            if(ratings[i] > ratings[i - 1]) obtain[i] = obtain[i - 1] + 1;
        }
        // 从后面向前面遍历
        for(int j = ratings.size() - 2 ; j >= 0 ; j --) {
            if(ratings[j] > ratings[j + 1]) obtain[j] = max(obtain[j] , obtain[j + 1] + 1);
        }
        int sum = 0;
        for(auto& val : obtain) {
            sum += val;
        }
        return sum;
    }
};