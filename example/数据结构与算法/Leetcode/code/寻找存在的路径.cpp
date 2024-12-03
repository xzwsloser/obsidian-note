/* 并查集 */
#include<iostream>
#include<vector>
using namespace std;

/* 初始化并查集 */
void init(vector<int>& father) {
    for(int i = 1 ; i < father.size() ; i ++) {
        father[i] = i;
    }
}

/* 查询节点,进行路径压缩操作 */
int find(vector<int>& father , int i) {
    return i == father[i] ? i : father[i] = find(father , father[i]);
}

/* 插入节点 */
void join(vector<int>& father , int i , int j) {
    int u = find(father , i);
    int v = find(father , j);
    if(u == v) return ;
    father[u] = v;
}

/* 判断节点是否在一个集合中 */
bool isSame(vector<int>& father , int i , int j) {
    int u = find(father , i);
    int v = find(father , j);
    return u == v;
}
int main() {
    int N , M ;
    cin >> N >> M ;
    vector<int> father(N + 1 , 0);
    init(father);
    int i , j;
    for(int i = 0 ; i < M ; i ++) {
        cin >> i >> j;
        join(father,i,j);
    }
    int start , end;
    cin >> start >> end;
    bool result = isSame(father , start , end);
    if(result) {
        cout << "successed!" << endl;
    } else {
        cout << "failed!" << endl;
    }
    return 0;
}
