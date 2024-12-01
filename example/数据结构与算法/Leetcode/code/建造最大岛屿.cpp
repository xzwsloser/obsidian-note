/* 建造岛屿 */
#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<unordered_set>
using namespace std;

const int direction[4][2] = {1, 0 , -1 , 0 , 0 , 1 , 0 , -1};
void dfs(vector<vector<int>>& island , int curx , int cury , int& result , int mark) {
    for(int i = 0 ; i < 4 ; i ++) {
        int newx = curx + direction[i][0] ;
        int newy = cury + direction[i][1] ;
        if(newx < 0 || newy < 0 || newx >= island.size() || newy >= island[0].size()) continue;
        if(island[newx][newy] == 1) {
            island[newx][newy] = mark;
            result ++;
            dfs(island , newx, newx, result , mark);   
        }
    }
}
int main() {
    int N , M ;
    cin >> N >> M ;
    vector<vector<int>> island(N , vector<int>(M , 0));
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            cin >> island[i][j] ;
        }
    }

    bool isAllGrid = true ;  /* 是否全部都是陆地 */
    unordered_map<int,int> area_table ;   /* 标记 - 陆地面积大小的 键值对集合 */
    int mark = 2;  /* 表示开始的标记 */
    for(int i = 0 ; i < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            if(island[i][j] == 0) isAllGrid = false ;
            if(island[i][j] == 1) {
                int result = 1;
                island[i][j] = mark;
                dfs(island , i , j , result , mark);
                area_table[mark] = result; 
                mark ++;
            }
        }
    }
    if(isAllGrid) return N * M ;
    int max_area = 0;
    unordered_set<int> visited_area ;
    for(int i = 0 ; i  < N ; i ++) {
        for(int j = 0 ; j < M ; j ++) {
            if(island[i][j] == 0) {
                visited_area.clear();
                int count = 1;
                for(int i = 0 ; i < 4 ; i ++) {
                    int newx = i + direction[i][0] ;
                    int newy = j + direction[i][1] ;
                    if(newx < 0 || newy < 0 || newx >= island.size() || newy >= island[0].size()) continue;
                    if(visited_area.count(island[newx][newy])) continue;
                    count += area_table[island[newx][newy]];
                    visited_area.insert(island[newx][newy]);
                }
                max_area = max(max_area , count);
            }
        }
    }
    cout << "the max area of island is " << max_area << endl;
    cout << endl;
    for(vector<int>& vec : island) {
        for(int& i : vec) {
            cout << i << " ";
        }
        cout << endl;
    }
}