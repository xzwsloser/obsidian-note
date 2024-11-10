#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int N , V;
    cin >> N >> V;
    vector<int> weight(N , 0);
    vector<int> value(N , 0);
    for(int i = 0 ; i < N ; i ++) {
        cin >> weight[i] >> value[i];
    }
    vector<int> dp(V + 1 , 0);
    for(int i = 0 ; i < N ; i ++) {
        for(int j = weight[i] ; j <= V ; j ++) {
            dp[j] = max(dp[j] , dp[j - weight[i]] + value[i]); 
        }
    }
    cout << dp[V] << endl;
}