#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int m , n;  // m 表示物品种类数量,n表示背包空间
    cin >> m >> n;
    vector<int> weight(m , 0);  // 表示物品的重量
    vector<int> value(m , 0);   // 表示物品的价值
    for(int i = 0 ; i < m ; i ++) {
        cin >> weight[i];
    }
    
    for(int j = 0 ; j < m ; j ++) {
        cin >> value[j];
    }
    // dp 数组的含义: dp[i][j] 表示索引范围为 [0,i]的物品任取并且背包容量
    // 为 j , 最大价值
    vector<vector<int>> dp(m , vector<int>(n + 1 , 0)); 
    // 1. 初始化
    for(int j = weight[0] ; j <= n ; j ++) dp[0][j] = value[0];
    // 2. 递推
    for(int i = 1 ; i < m ; i ++) {
        for(int j = 0 ; j <= n ; j ++) {
            if(j < weight[i]) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = max(dp[i - 1][j] , dp[i - 1][j - weight[i]] + value[i]);
        }
    }
    cout << dp[m - 1][n] << endl;
}