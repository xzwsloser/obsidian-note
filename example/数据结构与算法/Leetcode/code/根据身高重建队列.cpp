class Solution {
public:
    static bool cmp(const vector<int>& a , const vector<int>& b) {
        if(a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 1. 按照身高排序
        sort(people.begin() , people.end() , cmp);
        // 2. 按照后面的下标插入即可,这里可以使用list容器,但是由于list容器的迭代器不是随机访问的
        list<vector<int>> que;
        for(int i = 0 ; i < people.size() ; i ++) {
            int position = people[i][1];
            list<vector<int>>::iterator it = que.begin();
            while(position --) {
                it ++;
            }
            que.insert(it , people[i]);
        }
        return vector<vector<int>>(que.begin() , que.end());
    }
};