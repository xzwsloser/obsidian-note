/* 岛屿的最大面积 , dfs */
#include<iostream>
#include<vector>
using namespace std;

const int direction[4][2] = {1 , 0 , -1 , 0 , 0 , 1 , 0 , -1};
void dfs(const vector<vector<int>>& island , vector<vector<bool>>& visited , int curx , int cury , int& result) {
    for(int i = 0 ; i < 4 ; i ++) {
        int newx = curx + direction[i][0];
        int newy = cury + direction[i][1];
        if(newx < 0 || newy < 0 || newx >= island.size() || newy >= island[0].size()) continue;
        if(island[newx][newy] == 1 && !visited[newx][newy]) {
            result ++;
            visited[newx][newy] = true;
            dfs(island , visited , newx , newy , result);
        }
    }
}
int main() {
    int N , M ;
    cin >> N >> M ;
    vector<vector<int>> island(N , vector<int>(M , 0));
    vector<vector<bool>> visited(N , vector<bool>(M , false));
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            cin >> island[i][j];
        }
    }
    int max_area = 0;
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            if(island[i][j] == 1 && !visited[i][j]) {
                visited[i][j] = true;
                int result = 1;
                dfs(island , visited , i , j , result);
                max_area = max<int>(max_area , result);
            }
        }
    }
    cout << "the max area of island is " << max_area << endl;
}