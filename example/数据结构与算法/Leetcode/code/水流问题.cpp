/* 水流问题 */
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
const int direction[4][2] = {1 , 0 , -1 , 0 , 0  , 1 , 0 , -1};

void dfs(const vector<vector<int>>& island , vector<vector<bool>>& visited , int curx , int cury) {
    for(int i = 0 ; i < 4 ; i ++) {
        int newx = curx + direction[i][0];
        int newy = cury + direction[i][1];
        if(newx < 0 || newy < 0 || newx >= island.size() || newy >= island[0].size()) continue;
        if(island[newx][newy] >= island[curx][cury] && !visited[newx][newy]) {
            visited[newx][newy] = true;
            dfs(island , visited , newx , newy);
        }
    }
}

void bfs(const vector<vector<int>> &island , vector<vector<bool>>& visited , int curx , int cury) {
    queue<pair<int,int>> que;
    que.push({curx,cury});
    while(!que.empty()) {
        pair<int,int> cur = que.front();
        que.pop();
        for(int i = 0 ; i < 4 ; i ++) {
            int newx = cur.first + direction[i][0] ;
            int newy = cur.second + direction[i][1] ;
            if(newx < 0 || newy < 0 || newx >= island.size() || newy >= island[0].size()) continue;
            if(island[newx][newy] >= island[cur.first][cur.second] && !visited[newx][newy]) {
                visited[newx][newy] = true;
                que.push({newx,newy});
            }
        }
    }
}
int main() {
    int N , M ;
    cin >> N >> M ;
    vector<vector<int>> island(N , vector<int>(M , 0));
    vector<vector<bool>> visited1(N , vector<bool>(M , false)); /* 是否可以到达第一边界 */
    vector<vector<bool>> visited2(N , vector<bool>(M , false)); /* 是否可以到达第二边界*/
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            cin >> island[i][j] ;
        }
    }

    // 从边界出发
    for(int i = 0 ; i < N ; i ++) {
        visited1[i][0] = true;
        bfs(island , visited1 , i , 0);
        visited2[i][M - 1] = true;
        bfs(island , visited2 , i , M - 1);
    }

    for(int j = 0 ; j < M ; j ++) {
        visited1[0][j] = true;
        bfs(island , visited1 , 0 , j);
        visited2[N - 1][j] = true;
        bfs(island , visited2 , N - 1 , 0);
    }
    
    cout << endl;
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            if(visited1[i][j] && visited2[i][j]) {
                cout << i << " " <<  j << endl;
            }
        }
    }

}