class Solution {
public:
    unordered_map<string,map<string,int>> um;  // 存储这票的起点和终点
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        // 初始化 um
        for(const vector<string>& vec : tickets) {
            um[vec[0]][vec[1]] ++;
        }
        vector<string> result;
        result.push_back("JFK");
        dfs(result , tickets.size());
        return result;
    }
private:
    bool dfs(vector<string>& result , int ticketNum) {
        if(result.size() == ticketNum + 1) return true;
        for(pair<const string,int>& ticket : um[result.back()]) {
            if(ticket.second > 0) {
                result.push_back(ticket.first);
                ticket.second --;
                if(dfs(result , ticketNum)) return true;
                ticket.second ++;
                result.pop_back();
            }
        }
        return false;
    }
};
