class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        // 转换为 string
        string s = to_string(n);
        for(int i = 0 ; i < s.size() ; i ++) {
            if(i != s.size() - 1 && s[i] > s[i + 1]) {
                int j = i;
                while(j >= 0 && s[j] == s[i]) j --;
                j ++;
                s[j] -= 1;
                for(int k = j + 1 ; k < s.size() ; k ++) {
                    s[k] = '9';
                }
            }
        }
        return stoi(s);
    }
};


class Solution {
public:
    int monotoneIncreasingDigits(int n) {
        // 转换为 string
        string s = to_string(n);
        int flag = s.size();
        for(int i = s.size() - 1 ; i > 0 ; i --) {
            if(s[i - 1] > s[i]) {
                flag = i;
                s[i - 1] --;
            }
        }
        for(int i = flag ; i < s.size() ; i ++) {
            s[i] = '9';
        }
        return stoi(s);
    }
};