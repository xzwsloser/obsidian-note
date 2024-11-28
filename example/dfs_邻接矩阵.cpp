/*
    所有可达路径,使用邻接矩阵的方式存储
    dfs
*/
#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> result;
void dfs(const vector<vector<int>>& map , vector<int> & path , int cur , int target) {
    if(cur == target) {
        result.push_back(path);
        return ;
    }

    for(int i = 1 ; i <= target ; i ++) {
        if(map[cur][i] == 1) {
            path.push_back(i);
            dfs(map , path , i , target);
            path.pop_back();
        }
    }
}

int main() {
    int N , M;
    cin >> N >> M;
    vector<vector<int>> map(N + 1 , vector<int>(N + 1 , 0));
    int from , to;
    while(M --) {
        cin >> from >> to;
        map[from][to] = 1;
    }
    vector<int> path;
    path.push_back(1);
    dfs(map , path , 1 , N);
    for(vector<int>& vec : result) {
        for(int i = 0 ; i < vec.size() - 1 ; i ++) {
            cout << vec[i] << " ";
        }
        cout << vec.back() << endl;
    }
}