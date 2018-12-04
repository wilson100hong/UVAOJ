#include <iostream>
#include <vector>
#include <set>
#include <sstream>
using namespace std;

int min(int a, int b) {
    return a < b ? a : b;
}

void mark(vector<vector<bool>>& board, int r, int c) {
    board[r][c] = false;
    for (int i=0;i<8;++i) {
        board[r][i] = false;
        board[i][c] = false;
        // positive diagonal
        int j = r + c - i;
        if (j >= 0 && j < 8) {
            board[i][j] = false;
        }
        // negative diagonal
        j = c - r + i;
        if (j >= 0 && j < 8) {
            board[i][j] = false;
        }
    }
}

void dump(const vector<vector<bool>>& board) {
    for (int i=0;i<8;++i) {
        for (int j=0;j<8;++j) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

void dump_queens(const vector<int>& queens) {
    for (int q : queens) {
        cout << q;
    }
    cout << endl;
}

#define IMPOSSIBLE 1000
int rec(const vector<vector<bool>>& board, const vector<int>& queens, int col) {
    if (col == 8) {
        return 0;
    }
    int row = queens[col];
    
    int best = IMPOSSIBLE;
    for (int i=0;i<8;++i) {
        if (board[i][col]) {
            //queens[col] = i;
            vector<vector<bool>> new_board = board;
            mark(new_board, i, col);
            int cand = (i == row ? 0 : 1) + rec(new_board, queens, col+1);
            best = min(best, cand);
            if (best == 0) return 0;
        }
    }
    return best;
}

int solve(vector<int>& queens) {
    vector<vector<bool>> board(8, vector<bool>(8, true));
    return min(IMPOSSIBLE, rec(board, queens, 0));
}

int main() {
    string line;
    int T = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        vector<int> queens;
        int n;
        for (int i=0;i<8;++i) {
            ss >> n;
            queens.push_back(n-1);
        }
        cout << "Case " << ++T << ": " << solve(queens) << endl;
    }
}
