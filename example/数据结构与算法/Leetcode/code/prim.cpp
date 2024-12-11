/* 最小生成树 prim 算法 */
#include<iostream>
#include<vector>
using namespace std;
int main() {
    int v , e ;  /* 表示节点个数和边的个数 */
    int x , y , k ;
    cin >> v >> e;
    vector<vector<int>> grid(v + 1 , vector<int>(v + 1 , 10001));
    for(int i = 0 ; i < e ; i ++) {
        cin >> x >> y >> k ;
        grid[x][y] = k;
        grid[y][x] = k;
    }

    vector<bool> is_in_tree(v + 1 , false); /* 表示节点是否在树中 */
    vector<int> minDist(v + 1 , 10001);

    // prim 算法构建过程
    for(int i = 0 ; i < v - 1 ; i ++) {
        // 1. 首先挑选一个距离最小生成树最近的节点
        int minVal = __INT_MAX__;
        int cur = -1;
        for(int j = 1 ; j <= v ; j ++) {
            if(!is_in_tree[j] && minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            } 
        }

       // 2. 加入到最小生成树中
       is_in_tree[cur] = true;
       // 3. 更新 minDist
       for(int k = 1 ; k <= v ; k ++) {
        if(!is_in_tree[k] && grid[cur][k] < minDist[k]) {
            minDist[k] = grid[cur][k];
        }
       }
    } 
    int result = 0;
    for(int i = 2 ; i <= v ; i ++) {
        result += minDist[i];
    }
    cout << "minimum distance: " << result << endl;
    return 0;
}