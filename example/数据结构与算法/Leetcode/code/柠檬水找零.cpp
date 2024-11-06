class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
       // 5 --> 不需要找零
       // 10 ---> 5 * 1 
       // 20 ---> 10 + 5 或者 5 * 3
       // 所以可以尽量留下 5 元
       int fiveNum = 0 , tenNum = 0;  // 分别记录 5 元和 10 元的数量
       for(int i = 0 ; i < bills.size() ; i ++) {
            if(bills[i] == 5) {
                fiveNum ++;
            } else if(bills[i] == 10) {
                if(fiveNum == 0) return false;
                fiveNum --;
                tenNum ++;
            } else if(bills[i] == 20) {
                // 首先考虑 10 + 5
                if(fiveNum == 0) return false;
                if(tenNum != 0) {
                    tenNum --;
                    fiveNum --;
                } else if(tenNum == 0 && fiveNum < 3) {
                    return false;
                } else if(tenNum == 0 && fiveNum >= 3) {
                    fiveNum -= 3;
                }
            }
       }
       return true;
    }
};