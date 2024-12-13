/* dijkstra 算法堆优化版 */
#include<iostream>
#include<vector>
#include<list>
#include<climits>
#include<queue>
using namespace std;

typedef struct Edge {
    int to ;
    int val ;
    Edge(int to , int val) : to(to) , val(val) {}
} Edge;

class MyComparsion {
public:
    bool operator()(const pair<int,int>& lhs , const pair<int,int>& rhs) {
        return lhs.second > rhs.second ;
    }
};

int main() {
     int N , M ; /* N 表示节点个数 , M 表示边的个数 */
     cin >> N >> M ;
     int s , t , val;
     vector<list<Edge>> grid(N + 1);
     while(M --) {
        cin >> s >> t >> val;
        grid[s].push_back(Edge(t , val));
     } 

    int start = 1 ;
    int end = N ;
    vector<int> minDist(N + 1 , INT_MAX);
    minDist[start] = 0;
    vector<bool> visited(N + 1 , false);
    priority_queue<pair<int,int> , vector<pair<int,int>> , MyComparsion> pq ;
    pq.push({start , 0});
    while(!pq.empty()) {
        // 1. 找到距离源点最近的点
        pair<int,int> cur = pq.top();
        pq.pop();
        // 2. 设置为已经访问过
        if(visited[cur.first]) continue;
        visited[cur.first] = true;
        // 3. 更新节点到源点的距离
        for(Edge& e : grid[cur.first]) {
            if(!visited[e.to] && minDist[e.to] > e.val + cur.second) {
                minDist[e.to] = e.val + cur.second;
                pq.push({e.to , minDist[e.to]});
            }
        }
    }

    if(minDist[end] == INT_MAX)  cout << "-1" << endl;
    else cout << minDist[end] << endl;
    return 0;
}