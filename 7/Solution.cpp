#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> createBoard(int n) {
        vector<string> board;

        for (int i = 0; i < n; i++) {
            string row(n, '.');
            board.push_back(row);
        }

        return board;
    }

    bool isSafe(vector<string>& board, int i, int j, int n) {
        for (int x = i - 1; x >= 0; x--) {
            if (board[x][j] == 'Q') return false;
        }

        for (int x = i - 1, y = j - 1; (x >= 0 && y >= 0); x--, y--) {
            if (board[x][y] == 'Q') return false;
        }

        for (int x = i - 1, y = j + 1; (x >= 0 && y < n); x--, y++) {
            if (board[x][y] == 'Q') return false;
        }

        return true;
    }

    bool placeQueen(vector<string>& board, int i, int j, int n) {
        if (isSafe(board, i, j, n)) {
            board[i][j] = 'Q';
            return true;
        }
        return false;
    }

    bool solve(vector<string>& board, int row, int n, vector<vector<string>>& ans) {
        if (row == n) {
            addSolution(board, ans);
            return true;
        }

        bool flag = false;
        for (int column = 0; column < n; column++) {
            if (placeQueen(board, row, column, n)) {
                if (!solve(board, row + 1, n, ans)) {
                    board[row][column] = '.';
                } else {
                    board[row][column] = '.';
                    flag = true;
                }
            }
        }
        return flag;
    }

    void addSolution(vector<string>& board, vector<vector<string>>& ans) {
        ans.push_back(board);
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board = createBoard(n);
        vector<vector<string>> ans;

        solve(board, 0, n, ans);
        return ans;
    }
};

int main() {
    Solution solution;
    int n = 4; // Установите нужный размер доски
    vector<vector<string>> result = solution.solveNQueens(n);

    // Вывод результатов
    for (const auto& solution : result) {
        for (const string& row : solution) {
            cout << row << endl;
        }
        cout << "---------------------" << endl;
    }

    return 0;
}
