/* 字符串接龙 */
#include<iostream>
#include<queue>
#include<vector>
#include<unordered_set>
using namespace std;

int bfs(string& beginStr , string& endStr , unordered_set<string>& dict) {
    queue<string> que;
    que.push(beginStr);
    int result = 1;
    while(!que.empty()) {
        int n = que.size();
        for(int i = 0 ; i < n ; i ++) {
            string str = que.front();
            que.pop();
            // 改变字母类似于遍历过程
            for(int i = 0 ; i < str.size() ; i ++) {
                for(int j = 0 ; j < 26 ; j ++) {
                    string newstr = str;
                    newstr[i] = 'a' + j;
                    if(newstr == endStr) {
                        return result + 1; 
                    }
                    if(dict.count(newstr)) {
                        que.push(newstr);
                    }
                }
            }
        }
       result ++; // 表示一层
    }
    return 0;
}
int main() {
    int N ;
    cin >> N ;
    string beginStr ;
    string endStr ;
    cin >> beginStr >> endStr ;
    unordered_set<string> dict;
    string str;
    for(int i = 0 ; i < N ; i ++) {
        cin >> str;
        dict.insert(str);
    }
    cout << "the min step is " << bfs(beginStr , endStr , dict) << endl;
}