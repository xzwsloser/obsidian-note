class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalSum = 0;  // 记录总和
        int curSum = 0;  // 记录当前和
        int start = 0;
        for(int i = 0 ; i < gas.size() ; i ++) {
            totalSum += (gas[i] - cost[i]);
            curSum += (gas[i] - cost[i]);
            if(curSum < 0) {
                start = i + 1;
                curSum = 0;
            }
        }
        if(totalSum < 0) return -1;
        return start;
    }
};


class Solution1 {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curSum = 0;
        int min = INT_MAX;
        for(int i = 0 ; i < gas.size() ; i ++) {
            curSum += (gas[i] - cost[i]);
            if(curSum < min) {
                min = curSum;
            }
        }
        if(curSum < 0) return -1;
        if(min >= 0) return 0;
        for(int j = gas.size() - 1 ; j >= 0 ; j --) {
            min += (gas[j] - cost[j]);
            if(min >= 0) return j;
        }
        return -1;
    }
};