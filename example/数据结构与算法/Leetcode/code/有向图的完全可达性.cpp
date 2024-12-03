/* 有方向图的完全可达性,使用邻接表的方式存储 */
#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

void dfs(unordered_map<int,vector<int>>& map , vector<bool>& visited , int curNum) {
    for(int i = 0 ; i < map[curNum].size() ; i ++) {
        if(!visited[map[curNum][i]]) {
            visited[map[curNum][i]] = true;
            dfs(map , visited , map[curNum][i]) ;
        }
    }
}

void bfs(unordered_map<int,vector<int>>& map , vector<bool>& visited , int curNum) {
    queue<int> que;
    que.push(curNum);
    while(!que.empty()) {
        int cur = que.front();
        que.pop();
        for(int i = 0 ; i < map[cur].size() ; i ++) {
            int num = map[cur][i];
            if(!visited[num]) {
                visited[num] = true;
                que.push(num);
            }
        }
    }
}
int main() {
    int N , K ; /* N -> 节点个数 , K -> 边的个数*/
    cin >> N >> K ;
    unordered_map<int,vector<int>> map ;
    int from , to ;
    for(int i = 0 ; i < K ; i ++) {
        cin >> from >> to;
        map[from].push_back(to);
    }
    vector<bool> visited(N + 1 , false);
    visited[1] = true;
    // dfs(map , visited , 1);
    bfs(map , visited , 1);
    int flag = true;
    for(int i = 1 ; i < visited.size() ; i ++) {
        if(!visited[i]) {
            flag = false;
            cout << "failed !" << endl;
        }
    }
    if(flag) {
        cout << "successed !" << endl;
    }
    return 0;
}