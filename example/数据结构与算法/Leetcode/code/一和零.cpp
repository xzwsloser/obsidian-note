class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<vector<int>>> dp(strs.size() , vector<vector<int>>(m + 1 , vector<int>(n + 1 , 0)));
        // 初始化
        vector<int> counter = count(strs[0]);
        for(int i = 0 ; i <= m ; i ++) {
            for(int j = 0 ; j <= n ; j ++) {
                if(i >= counter[0] && j >= counter[1]) {
                    dp[0][i][j] = 1;
                }
            }
        }

        // 递推
        for(int i = 1 ; i < strs.size() ; i ++) {
            for(int j = 0 ; j <= m ; j ++) {
                for(int k = 0 ; k <= n ; k ++) {
                    counter = count(strs[i]);
                    if(j >= counter[0] && k >= counter[1]) {
                        dp[i][j][k] = max(dp[i - 1][j][k] , dp[i - 1][j - counter[0]][k - counter[1]] + 1);
                    } else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }     
                }
            }
        }
        return dp[strs.size() - 1][m][n];
    }
private:
    vector<int> count(string& s) {
        vector<int> result(2 , 0);
        for(char& ch : s) {
            if(ch == '0') result[0] ++;
            else if(ch == '1') result[1] ++;
        }
        return result;
    }
};


class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
       // 二维数组
       vector<vector<int>> dp(m + 1 , vector<int>(n + 1 , 0));
       vector<int> counter;
       for(int i = 0 ; i < strs.size() ; i ++) {
            counter = count(strs[i]);
            for(int j = m ; j >= counter[0] ; j --) {
                for(int k = n ; k >= counter[1] ; k --) {
                    dp[j][k] = max(dp[j][k] , dp[j - counter[0]][k - counter[1]] + 1);
                }
            }
       }
       return dp[m][n];
    }
private:
    vector<int> count(string& s) {
        vector<int> result(2 , 0);
        for(char& ch : s) {
            if(ch == '0') result[0] ++;
            else if(ch == '1') result[1] ++;
        }
        return result;
    }
};
