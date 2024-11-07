class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() == 1) return intervals;
        vector<vector<int>> result;  /* 用于记录结果 */
        sort(intervals.begin() , intervals.end() , [](const vector<int>& a , const vector<int>& b) -> bool {
            return a[0] < b[0];
        });
        int startIndex = intervals[0][0];
        int endIndex = intervals[0][1];
        for(int i = 1 ; i < intervals.size() ; i ++) {
            // 重叠
            if(intervals[i][0] <= endIndex) {
                endIndex = max(endIndex , intervals[i][1]);
            } else {
                result.push_back(vector<int>({startIndex , endIndex}));
                startIndex = intervals[i][0];
                endIndex = intervals[i][1];
            }

            if(i == intervals.size() - 1) {
                // 最后一个区间,可以直接合并了
                result.push_back(vector<int>({startIndex , endIndex}));
            }
        }
        return result;
    }
};


class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() == 1) return intervals;
        vector<vector<int>> result;  /* 用于记录结果 */
        sort(intervals.begin() , intervals.end() , [](const vector<int>& a , const vector<int>& b) -> bool {
            return a[0] < b[0];
        });
        result.push_back(intervals[0]);
        for(int i = 1 ; i < intervals.size() ; i ++) {
            if(intervals[i][0] <= result.back()[1]) {
                result.back()[1] = max(result.back()[1] , intervals[i][1]);
            } else {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};