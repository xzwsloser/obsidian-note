class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // 贪心算法,把小饼干分给为口小的孩子
        sort(g.begin() , g.end());
        sort(s.begin() , s.end());
        int i = 0 , j = 0;
        while(i < g.size() && j < s.size()) {
            // 首先找到位置
            while(j < s.size() && s[j] < g[i]) j ++;
            if(j == s.size()) break;
            if(s[j] >= g[i]) i ++;
            j ++;
        }
        return i;
    }
};