/* dijkstra 算法 求解最短路径 */
#include<iostream>
#include<vector>
using namespace std;

int main() {
    int N , M ; /* 表示节点个数和边的个数 */
    cin >> N >> M ;
    vector<vector<int>> grid(N + 1 , vector<int>(N + 1 , __INT_MAX__));
    int s, t , val;
    while(M --) {
        cin >> s >> t >> val;
        grid[s][t] = val;
    }

    int start = 1 , end = N ;
    vector<int> minDist(N + 1 , __INT_MAX__);
    vector<bool> visited(N + 1 , false);

    minDist[start] = 0;
    for(int i = 1 ; i <= N ; i ++) {
        // 1. 首先找到距离源点最近的节点
        int minVal = __INT_MAX__;
        int cur = -1;
        for(int j = 1 ; j <= N ; j ++) {
            if(!visited[j] && minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            }
        }
        // 2. 访问这一个节点
        visited[cur] = true;

        // 3. 更新到源点的距离
        for(int k = 1 ; k <= N ; k ++) {
            if(!visited[k] && grid[cur][k] != __INT_MAX__ && grid[cur][k] + minDist[cur] < minDist[k]) {
                minDist[k] = grid[cur][k] + minDist[cur];
            }
        }
    }

    if(minDist[end] == __INT_MAX__) cout << "-1" << endl;
    else cout << minDist[end] << endl;
}