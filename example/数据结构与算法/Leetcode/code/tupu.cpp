/* 拓扑排序 */
#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;

int main() {
    int N , M ;
    int s , t;
    cin >> N >> M ;
    unordered_map<int,vector<int>> umap ;
    vector<int> result; 
    queue<int> que;
    vector<int> InDegree(N , 0);
    while(M --) {
        cin >> s >> t ;
        InDegree[t] ++;
        umap[s].push_back(t);
    }
    
    // 首先找到入度为 0 的节点
    for(int i = 0 ; i < N ; i ++) {
        if(InDegree[i] == 0) {
            que.push(i);
        }
    }


    while(!que.empty()) {
        int cur = que.front();
        que.pop();
        result.push_back(cur); 
        
        for(int& i : umap[cur]) {
            InDegree[i] --;
            if(InDegree[i] == 0) {
                que.push(i);
            }
        }
    }

    if(result.size() == N) {
        for(int i = 0 ; i < N - 1 ; i ++) {
            cout << result[i] << " ";
        }
        cout << result[N - 1] << endl;
    } else {
        cout << "-1" << endl;
    }
    
    return 0;
}