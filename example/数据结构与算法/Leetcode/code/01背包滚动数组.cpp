#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int m ,  n;  // m 表示物品的种类数量 , n 表示背包的容量
    cin >> m >> n;
    vector<int> weight(m , 0);  // 物品的重量
    vector<int> value(m , 0);   // 物品的价值
    for(int i = 0 ; i < m ; i ++) {
        cin >> weight[i];
    }
    
    for(int i = 0 ; i < m ; i ++) {
        cin >> value[i];
    }
    
    vector<int> dp(n + 1 , 0);  // dp[j] 表示背包容量为 j 的时候最大价值
    // 此时任意选取索引为 0 - i 内的数
    // 初始化为 0 即可,注意索引从 0 开始
    for(int i = 0 ; i < m ; i ++) {
        for(int j = n ; j >= weight[i] ; j --) {
            dp[j] = max(dp[j] , dp[j - weight[i]] + value[i]);
        }
    }
    cout << dp[n] << endl;
}