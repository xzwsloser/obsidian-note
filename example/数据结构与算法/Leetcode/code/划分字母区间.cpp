class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> result;
        int i = 0;
        int j = s.size() - 1;
        int maxIndex = 0;  // 记录最大索引
        int startIndex = 0;  // 记录开始索引
        while(i < s.size()) {
            // 只需要对于 i 进行操作即可
            j = s.size() - 1;
            while(s[j] != s[i]) j --;
            maxIndex = max(maxIndex , j);
            if(i == maxIndex) {
                result.push_back(maxIndex - startIndex + 1);
                startIndex = i + 1;
            }
            i ++;
        }
        return result;
    }
};

// 利用哈希表 + unordered_set 集合的方式
class Solution {
public:
    vector<int> partitionLabels(string s) {
       vector<int> result;
       int startIndex = 0;
       // 首先记录字母出现次数
       int hash[26] = {0};
       for(char& ch : s) hash[ch - 'a'] ++;
       unordered_set<char> us;  // 用于记录遍历到的元素
       for(int i = 0 ; i < s.size() ; i ++) {
            char ch = s[i];
            us.insert(ch);
            hash[ch - 'a'] --;
            if(hash[ch - 'a'] == 0) {
                us.erase(us.find(ch));
                if(us.empty()) {
                    result.push_back(i - startIndex + 1);
                    startIndex = i + 1;
                }
            } 
       }
       return result;
    }
};


class Solution {
public:
    vector<int> partitionLabels(string s) {
       vector<int> result;
       // 1. 首先记录每一个元素出现的最远索引
       int hash[26] = {0};
       for(int i = 0 ; i < s.size() ; i ++) hash[s[i] - 'a'] = i;
       // 2. 记录边界即可
       int left = 0;
       int right = 0;
       for(int i = 0 ; i < s.size() ; i ++) {
            right = max(right , hash[s[i] - 'a']);
            if(i == right) {
                result.push_back(right - left + 1);
                left = i + 1;
            }
       }
       return result;
    }
};

