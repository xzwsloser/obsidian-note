class Solution {
public:
    vector<vector<string>> result;
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chessBoard(n , string(n , '.'));
        backtracking(chessBoard , 0 , n);
        return result;
    }
private:
    void backtracking(vector<string>& chessBoard , int row , int n) {
        if(row == n) {
            result.push_back(chessBoard);
            return ;
        }
        for(int i = 0 ; i < n ; i ++) {
            if(isVaild(chessBoard , row , i , n)) {
                chessBoard[row][i] = 'Q';
                backtracking(chessBoard , row + 1 , n);
                chessBoard[row][i] = '.';
            }
        }
    }
    bool isVaild(vector<string>& chessBoard , int row , int col , int n) {
        for(int i = 0 ; i < row ; i ++) {
            if(chessBoard[i][col] == 'Q') return false;
        }
        // 45度线
        for(int i = row - 1 , j = col + 1 ; i >= 0 && j < n ; i -- , j ++) {
            if(chessBoard[i][j] == 'Q') return false;
        }
        // 135度线
        for(int i = row - 1 , j = col - 1 ; i >= 0 && j >= 0 ; i -- , j --) {
            if(chessBoard[i][j] == 'Q') return false;
        }
        return true;
    }
};