/* SPFA 算法 */
#include<iostream>
#include<vector>
#include<queue>
#include<list>
#include<climits>
using namespace std;

typedef struct Edge {
    int to ;
    int val ;
    Edge(int to , int val): to(to) , val(val) {} 
} Edge ;

int main() {
    int N , M ;
    cin >> N >> M ;
    vector<list<Edge>> grid(N + 1);
    vector<bool> Inquque(N + 1 , false);
    int from , to , val;
    while(M --) {
        cin >> from >> to >> val;
        grid[from].push_back(Edge(to , val));
    } 

    vector<int> minDist(N + 1 , INT_MAX);
    int start = 1;
    int end = N ;
    minDist[start] = 0;
    queue<int> que;
    que.push(start);
    Inquque[start] = true;
    while(!que.empty()) {
        int cur = que.front();
        que.pop();
        Inquque[cur] = false;

        for(Edge& edge : grid[cur]) {
            if(minDist[cur] != INT_MAX && minDist[cur] + edge.val < minDist[edge.to]) {
                if(!Inquque[edge.to]) {
                    minDist[edge.to] = minDist[cur] + edge.val ;
                    Inquque[edge.to] = true;
                    que.push(edge.to);
                }
            }
        }
    }

    if(minDist[end] == INT_MAX) cout << "unconnected" << endl;
    else cout << minDist[end] << endl;
    return 0;
}