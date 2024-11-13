#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int bagWeight,n;
    cin >> bagWeight >> n;
    vector<int> weight(n , 0);
    vector<int> value(n , 0);
    vector<int> num(n , 0);
    for(int i = 0 ; i < n ; i ++) {
        cin >> weight[i];
    }
    
    for(int i = 0 ; i < n ; i ++) {
        cin >> value[i];
    }
    
    for(int i = 0 ; i < n ; i ++) {
        cin >> num[i];
    }
    
    vector<int> dp(bagWeight + 1 , 0);
    for(int i = 0 ; i < n ; i ++) {
        for(int j = bagWeight ; j >= weight[i] ; j --) {
            for(int k = 1 ; k <= num[i] && (j - k*weight[i]) >= 0 ; k ++) {
                dp[j] = max(dp[j] , dp[j - k*weight[i]] + k*value[i]);
            }
        }
    }
    cout << dp[bagWeight] << endl;
}