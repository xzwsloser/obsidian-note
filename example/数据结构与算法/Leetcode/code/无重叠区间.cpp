class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        // 两个区间的重叠情况
        sort(intervals.begin() , intervals.end() , [](const vector<int>& a , const vector<int>& b) -> bool {
            return a[0] < b[0];
        });
        int result = 0;
        int end = intervals[0][1];
        for(int i = 1 ; i < intervals.size() ; i ++) {
            if(intervals[i][0] < end) {
                // 此时发生了重叠,去除区间
                result ++;
                end = min(end , intervals[i][1]);
            } else {
                end = intervals[i][1];  // 更新最大区间
            }
        }
        return result;
    }
};