#include<iostream>
#include<vector>
using namespace std;
int main()
{
    // 递推公式: dp[i] = dp[i - 1] + dp[i - 2] + ... + dp[i - m]
    int n , m ;  /* n表示楼梯级数,m表示每一次最多可以爬多少级 */
    cin >> n >> m;
    vector<int> dp(n + 1 , 0);
    dp[0] = 1;
    for(int i = 1 ; i <= n ; i ++) {
        int j = i - m > 0 ? (i - m) : 0;
        for( ; j <= i - 1 ; j ++) {
            dp[i] += dp[j];
        }
    }
    cout << dp[n] << endl;
}


#include<iostream>
#include<vector>
using namespace std;
int main()
{
    // 利用背包问题求解
    // 排列问题
    int n , m;
    cin >> n >> m;
    vector<int> dp(n + 1 , 0);
    dp[0] = 1;
    for(int i = 1 ; i <= n ; i ++) {
        for(int j = 1 ; j <= m ; j ++) {
            if(i >= j) {
                dp[i] += dp[i - j];
            }
        }
    }
    cout << dp[n] << endl;
}