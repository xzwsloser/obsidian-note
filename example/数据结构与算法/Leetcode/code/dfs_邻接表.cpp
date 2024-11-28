/* dfs的邻居表的写法 */
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

vector<vector<int>> result; /* 记录结果 */
void dfs(unordered_map<int,vector<int>>& map , vector<int>& path , int N , int cur) {
    if(cur == N) {
        result.push_back(path);
        return ;
    }

    for(int& i : map[cur]) {
        path.push_back(i);
        dfs(map , path , N , i);
        path.pop_back();   
    }
}

int main() {
    int N , M ;
    cin >> N >> M ;
    unordered_map<int,vector<int>> map;
    int from,to;
    while(M --) {
       cin >> from >> to;
       map[from].push_back(to); 
    }

    vector<int> path;
    path.push_back(1);
    dfs(map , path , N , 1);
    for(vector<int>& vec : result) {
        for(int i = 0 ; i < vec.size() - 1 ; i ++) {
            cout << vec[i] << " ";
        } 
        cout << vec[vec.size() - 1] << endl;
    }
    return 0;
}