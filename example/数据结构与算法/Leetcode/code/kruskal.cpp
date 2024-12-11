/* krusal 算法 */
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define N 1001

typedef struct Edge {
    int x ;
    int y ;
    int val;
    Edge() {}
    Edge(int x, int y , int val): x(x) , y(y) , val(val) {}
} Edge ;

vector<int> father(N , 0);

/* 初始化并查集 */
void init() {
    for(int i = 0 ; i < N ; i ++) {
        father[i] = i;
    }
}

int find(int i) {
    return i == father[i] ? i : father[i] = find(father[i]);
}

void join(int i , int j ) {
    int u = find(i);
    int v = find(j);
    if(u == v) return ;
    father[u] = v;
}

bool isSame(int i , int j) {
    int u = find(i);
    int v = find(j);
    return u == v;
}

int main() {
    int v , e;
    cin >> v >> e;
    vector<Edge> edges; /* 记录边 */
    int x , y , val;
    while(e --) {
        cin >> x >> y >> val;
        edges.push_back(Edge(x,y,val));
    }

    sort(edges.begin() , edges.end() , [](const Edge& a, const Edge& b) -> bool {
        return a.val < b.val ;
    });

    init();

    int result = 0;
    for(Edge& e : edges) {
        int x = e.x ;
        int y = e.y ;
        if(isSame(x,y)) {
            continue;
        } else {
            result += e.val;
            join(x,y);
        }
    } 
    
    cout << "minimum distance " << result << endl;
}