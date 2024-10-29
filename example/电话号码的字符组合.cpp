class Solution {
public:
    vector<string> mapping;
    vector<string> res;
    string path;
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return res;
        mapping.resize(10);
        mapping[2] = "abc";
        mapping[3] = "def";
        mapping[4] = "ghi";
        mapping[5] = "jkl";
        mapping[6] = "mno";
        mapping[7] = "pqrs";
        mapping[8] = "tuv";
        mapping[9] = "wxyz";
        backtracking(digits , 0);
        return res;
    }
private:
    void backtracking(string digits , int curIndex) {
        if(path.size() == digits.size()) {
            res.push_back(path);
            return ;
        }
        for(char& ch : mapping[digits[curIndex] - '0']) {
            path.push_back(ch);
            backtracking(digits , curIndex + 1);
            path.pop_back();
        }
    }
};