/* 冗余连接 II */
#include<iostream>
#include<vector>
using namespace std;

vector<int> father(1001,0);
/* 并查集模板 */
void init(vector<int>& father) {
    for(int i = 1 ; i < father.size() ; i ++) father[i] = i;
}

int find(vector<int>& father , int i) {
    return i == father[i] ? i : father[i] = find(father,father[i]);
}

void join(vector<int>& father , int i , int j) {
    int u = find(father , i);
    int v = find(father , j);
    if(u == v) return ;
    father[u] = v;
}

bool isSame(vector<int>& father , int i , int j) {
    int u = find(father , i);
    int v = find(father , j);
    return u == v;
}

/* 判断删除之后的是否是一个有向的树 */
bool isTreeAfterDel(int delIndex , vector<pair<int,int>>& edges) {
    // 初始化
    for(int i = 0 ; i < edges.size() ; i ++) {
        if(i == delIndex) continue;
        if(isSame(father , edges[i].first , edges[i].second)) {
            return false;
        }
        join(father , edges[i].first , edges[i].second); 
    }
    return true;
}

int main() {
    int N ;  /* 记录节点个数 */
    int s , t ;  /* 记录节点的值 */
    cin >> N ;
    vector<int> inDegree(N + 1,0);
    vector<pair<int,int>> edges;  /* 记录边 */
    for(int i = 0 ; i < N ; i ++) {
        cin >> s >> t;
        inDegree[t] ++;
        edges.push_back({s,t});
    }
    /* 找到入度为 2 的节点 */
    vector<int> targetIndex;
    for(int i = N - 1 ; i >= 0 ; i --) {
        if(inDegree[edges[i].second] == 2) {
            targetIndex.push_back(i);
        }
    }
    cout << "=======ans========" << endl;
    init(father);
    /* 如果有入度为 2 的点 */
    if(!targetIndex.empty()) {
        if(isTreeAfterDel(targetIndex[0],edges)) {
            cout << edges[targetIndex[0]].first << "  " << edges[targetIndex[0]].second << endl;
        } else {
            cout << edges[targetIndex[1]].first << "  " << edges[targetIndex[1]].second << endl;
        }
        return 0;
    }    
    /* 如果没有就需要删除一条边 */
    for(int i = 0 ; i < edges.size() ; i ++) {
        if(isSame(father , edges[i].first , edges[i].second)) {
            cout << edges[i].first << "  " << edges[i].second << endl;
            break; 
        }
        join(father , edges[i].first , edges[i].second);
    }
    return 0;
}