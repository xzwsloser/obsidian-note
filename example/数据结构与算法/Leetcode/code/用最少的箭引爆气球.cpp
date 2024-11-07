class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin() , points.end() , [](const vector<int>& a , const vector<int>& b) -> bool {
            if(a[0] == b[0]) return a[1] < b[1];
            return a[0] < b[0];
        });
        int result = 1;
        int end = points[0][1];
        // 注意 end 的更新
        for(int i = 1 ; i < points.size() ; i ++) {
            if(points[i][0] > end) {
                result ++;
                end = points[i][1];
            } else {
                end = min(end , points[i][1]);
            }
        }
        return result;
    }
};