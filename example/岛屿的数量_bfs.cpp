/* 岛屿的数量 bfs */
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int direction[4][2] = {1 , 0 , -1 , 0 , 0 , 1 , 0 , -1};
void bfs(const vector<vector<int>>& island , vector<vector<bool>>& visited , int curx , int cury) {
    queue<pair<int,int>> que;
    que.push({curx,cury});
    while(!que.empty()) {
        pair<int,int> cur = que.front();
        que.pop();
        for(int i = 0 ; i < 4 ; i ++) {
            int newx = cur.first + direction[i][0];
            int newy = cur.second + direction[i][1];
            if(newx < 0 || newx >= island.size() || newy < 0 || newy >= island[0].size()) continue;
            if(island[newx][newy] == 1 && !visited[newx][newy]) {
                que.push({newx,newy});
                visited[newx][newy] = true;
            }
        }
    } 
}
int main() {
    int N , M;
    int result = 0;
    cin >> N >> M ;
    vector<vector<int>> island(N , vector<int>(M , 0));
    vector<vector<bool>> visited(N , vector<bool>(M , false));
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            cin >> island[i][j];
        }
    }

    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            if(island[i][j] == 1 && !visited[i][j]) {
                visited[i][j] = true;
                bfs(island, visited , i , j);
                result ++;
            }
        }
    }
    cout << "the number of island is " << result << endl;
}