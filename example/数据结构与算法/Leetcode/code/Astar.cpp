/* Astar 算法 */
#include<iostream>
#include<vector>
#include<queue>
#include<string.h>
#include<stdlib.h>
using namespace std;

const int direction[8][2] = {1 , 2 , -1 , 2 , 2 , 1 , -2 , 1 , -1 , -2 , 1 , -2 , 2 , -1 , -2 , -1};
int moves[1001][1001] ; /* 表示棋盘 */
int b1 , b2 ;  /* 终点坐标 */
class Knight {
public:
    int x , y ;  /* 表示坐标 */
    int g , h , f;  /* g 表示到起点的距离,h表示到终点的距离,f = g + h */
    bool operator < (const Knight& k) const { // 注意利用常对象才可使用
        return k.f < f ;
    }
};

priority_queue<Knight> que; /* 需要使用的优先队列 */

int Distance(const Knight& k) {
    return (k.x - b1) * (k.x - b1)  + (k.y - b2) * (k.y - b2);
}

void astar(Knight& k) {
    que.push(k);
    while(!que.empty()) {
        Knight cur = que.top();
        que.pop();
        if(cur.x == b1 && cur.y == b2) break;
        for(int i = 0 ; i < 8 ; i ++) {
            Knight next ;
            next.x = cur.x + direction[i][0];
            next.y = cur.y + direction[i][1];
            if(next.x <= 0 || next.y <= 0 || next.x >= 1000 || next.y >= 1000) continue;
            if(!moves[next.x][next.y]) {
                moves[next.x][next.y] = moves[cur.x][cur.y] + 1;
                next.g = cur.g + 5;
                next.h = Distance(next);
                next.f = next.g + next.h ;
                que.push(next);
            }
        }
    }
}

int main() {
    int n , a1 , a2 ;
    cin >> n ;
    while(n --) {
        cin >> a1 >> a2 >> b1 >> b2;
        Knight start ;
        memset(moves , 0 , sizeof(moves));
        start.x = a1 ;
        start.y = a2 ;
        start.g = 0;
        start.h = Distance(start);
        start.f = start.g + start.h ;
        astar(start);
        while(!que.empty()) que.pop();
        cout << moves[b1][b2] << endl;
    }
    return 0;
}