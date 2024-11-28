/* 岛屿的数量,dfs */
#include<iostream>
#include<vector>
using namespace std;

const int direction[4][2] = {-1 , 0 , 1 , 0 , 0 , -1 , 0 , 1};
void dfs(const vector<vector<int>>& island , int curx , int cury , vector<vector<bool>>& visited) {
    for(int i = 0 ; i < 4 ; i ++) {
        int newx = curx + direction[i][0];
        int newy = cury + direction[i][1];
        if(newx < 0 || newx >= island.size() || newy < 0 || newy >= island[0].size()) continue;
        if(island[newx][newy] == 1 && !visited[newx][newy]) {
            visited[newx][newy] = true;
            dfs(island , newx , newy , visited);
        }
    }
}
int main() {
    int N , M ;
    cin >> N >> M ; /* N -> 行数 , M -> 列数 */
    vector<vector<int>> island(N , vector<int>(M , 0));
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            cin >> island[i][j];
        }
    }
    vector<vector<bool>> visited(N , vector<bool>(M , false)); 
    int result = 0;
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            if(island[i][j] == 1 && !visited[i][j]) {
                visited[i][j] = true;
                dfs(island , i , j , visited);
                result ++;
            }
        }
    }
    cout << "the number of island is " << result << endl;
    return 0;
}