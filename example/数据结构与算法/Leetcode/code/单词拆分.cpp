class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // 完全背包问题
        unordered_set<string> us(wordDict.begin() , wordDict.end());
        vector<bool> dp(s.size() + 1 , false);
        dp[0] = true;
        // dp[j]  表示字符串长度为 i 的时候可以组成
        for(int i = 1 ; i <= s.size() ; i ++) {
            for(int j = 0 ; j < i ; j ++) {
                string str = s.substr(j , i - j); // [j , i - 1]  --> i - j + 1 
                if(us.find(str) != us.end() && dp[j]) {
                    dp[i] = true;
                }
            }
        }
        return dp[s.size()];
    }
};