/* 利用二维数字优化floyd算法 */
#include<iostream>
#include<vector>
using namespace std;
int main() {
    int n , m , s , t , val;
    cin >> n >> m ;
    vector<vector<int>> grid(n + 1 , vector<int>(n + 1 , 1005));
    while(m --) {
        cin >> s >> t >> val;
        grid[s][t] = val;
        grid[t][s] = val;
    }

    for(int k = 1 ; k <= n ; k ++) {
        for(int i = 1 ; i <= n ; i ++) {
            for(int j = 1 ; j <= n ; j ++) {
                grid[i][j] = min(grid[i][j] , grid[i][k] + grid[k][j]);
            }
        }
    }

    int start , end  , q;
    cin >> q;
    while(q --) {
        cin >> start >> end;
        if(grid[start][end] == 1005) cout << "-1" << endl;
        else cout << grid[start][end] << endl;
    }
    return 0;
}