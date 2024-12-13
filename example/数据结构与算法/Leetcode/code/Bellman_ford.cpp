/* Bellman_ford算法,可以用于处理负值回路,但是注意避免负权回路 */
#include<iostream>
#include<vector>
#include<climits>
using namespace std;
int main() {
    int N , M ;  /* N 表示节点个数, M 表示边的个数 */
    int s , t , val;
    cin >> N >> M ;
    vector<vector<int>> grid;
    while(M --) {
        cin >> s >> t >> val;
        grid.push_back({s , t , val});
    }
    vector<int> minDist(N + 1 , INT_MAX);
    int start = 1;
    int end = N ;
    minDist[start] = 0;
    // 对于每一条边松弛 N - 1 次即可
    for(int i = 0 ; i < N - 1 ; i ++) {
        // 需要对于所有边进行松弛操作
        for(vector<int>& edge : grid) {
            int from = edge[0];
            int to = edge[1];
            int val = edge[2];
            if(minDist[from] != INT_MAX && minDist[to] > minDist[from] + val) {
                minDist[to] = minDist[from] + val;
            }
        }
    }

    if(minDist[end] == INT_MAX) cout << "unconnected" << endl;
    else cout << minDist[end] << endl;
    return 0;
}