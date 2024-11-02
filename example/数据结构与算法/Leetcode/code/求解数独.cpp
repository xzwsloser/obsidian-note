class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);  
    }
private:
    // 一旦填充所有数字立刻返回 true 即可
    bool backtracking(vector<vector<char>>& board) {
        for(int i = 0 ; i < board.size() ; i ++) {
            for(int j = 0 ; j < board[0].size() ; j ++) {
                if(board[i][j] != '.') continue; 
                // 找到合适的位置
                for(char value = '1' ; value <= '9' ; value ++) {
                    if(isVaild(board , i , j , value)) {
                        board[i][j] = value;
                        if(backtracking(board)) return true;
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    // 判断位置是否合法
    bool isVaild(vector<vector<char>>& board , int row , int col , char target)  {
        // 检查行
        for(int i = 0 ; i < board[0].size() ; i ++) {
            if(i != col && board[row][i] == target) return false;
        }
        // 检查列
        for(int j = 0 ; j < board.size() ; j ++) {
            if(j != row && board[j][col] == target) return false;
        }
        // 检查九宫格
        int start_row = (row / 3) * 3;
        int start_col = (col / 3) * 3;
        for(int i = start_row ; i < start_row + 3 ; i ++) {
            for(int j = start_col ; j < start_col + 3 ; j ++) {
                if(i != row && j != col && board[i][j] == target) return false;
            }
        }
        return true;
    }
};