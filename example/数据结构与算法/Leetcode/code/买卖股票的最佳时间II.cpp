class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        int low = 0;
        while(low < prices.size() - 1) {
            if(prices[low] >= prices[low + 1]) {
                low ++;
            } else {
                // 接下来要找到最高点
                int high = low + 1;
                while(high < prices.size() - 1 && prices[high] <= prices[high + 1]) {
                    high ++;
                }
                result += (prices[high] - prices[low]);
                low = high;
            }
        }
        return result;
    }
};



// 代码随想录
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int result = 0;
        for(int i = 1 ; i < prices.size() ; i ++) {
            result += max(prices[i] - prices[i - 1] , 0);
        }
        return result;
    }
};