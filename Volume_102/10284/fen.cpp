#include <iostream>
#include <vector>
using namespace std;


// 0: empty
// 1: occupied
// 2: attacked
typedef vector<vector<char>> Chessboard;

#define EMPTY '.'
#define ATTACK 'X'

void dump(const Chessboard& board) {
    for (int r=0;r<8;++r) {
        for (int c=0;c<8;++c) {
            cout << board[r][c];
        }
        cout << endl;
    }
}

bool occupied(const Chessboard& board, int row, int col) {
    return !(board[row][col] == EMPTY || board[row][col] == ATTACK);
}

bool valid(int row, int col) {
    return 0 <= row && row < 8 && 0 <= col && col < 8;
}

void attack(Chessboard& board, int row, int col) {
    if (valid(row, col) && !occupied(board, row, col)) {
        board[row][col] = ATTACK;
    }
}

void start(Chessboard& board, int row, int col) {
    char c = board[row][col];
    if (c =='p') {
        attack(board, row+1, col-1);
        attack(board, row+1, col+1);
    }
    if (c == 'P') {
        attack(board, row-1, col-1);
        attack(board, row-1, col+1);
    }
    if (c == 'n' || c == 'N') {
        // Knight
        for (int dr=-1;dr<=1;dr+=2) {
            for (int dc=-2;dc<=2;dc+=4) {
                attack(board, row+dr, col+dc);
            }
        }
        for (int dr=-2;dr<=2;dr+=4) {
            for (int dc=-1;dc<=1;dc+=2) {
                attack(board, row+dr, col+dc);
            }
        }
    }
    if (c == 'b' || c == 'B' || c == 'q' || c == 'Q') {
        // Bishop & Queen
        // 4 directions
        for (int dr=-1;dr<=1;dr+=2) {
            for (int dc=-1;dc<=1;dc+=2) {
                int r = row + dr, c = col + dc;
                while (valid(r, c) && !occupied(board, r, c)) {
                    attack(board, r, c);
                    r+=dr;
                    c+=dc;
                }
            }
        }
    }
    if (c == 'r' || c == 'R' || c == 'q' || c == 'Q') {
        // Rook & Queen
        for (int dr=-1;dr<=1;dr+=2) {
            int r = row + dr, c = col;
            while (valid(r, c) && !occupied(board, r, c)) {
                attack(board, r, c);
                r+=dr;
            }
        }

        for (int dc=-1;dc<=1;dc+=2) {
            int r = row, c = col + dc;
            while (valid(r, c) && !occupied(board, r, c)) {
                attack(board, r, c);
                c+=dc;
            }
        }
    }
    if (c == 'k' || c == 'K') {
        // King
        for (int dr=-1;dr<=1;++dr) {
            for (int dc=-1;dc<=1;++dc) {
                attack(board, row+dr, col+dc);
            }
        }
    }
}

int solve(const string& input) {
    Chessboard board(8, vector<char>(8, EMPTY));
    int row = 0, col = 0;
    for (int i=0;i<input.size();++i) {
        char c = input[i];
        if (c == '/') {
            row++;
            col = 0;
        } else if ('1' <= c && c <= '8') {
            col += (c - '0');
        } else {
            board[row][col] = c;
            col++;
        }
    }

    for (int r=0;r<8;++r) {
        for (int c=0;c<8;++c) {
            start(board, r, c);
        }
    }

    int ans = 0;
    // dump(board);
    for (int r=0;r<8;++r) {
        for (int c=0;c<8;++c) {
            if (board[r][c] == EMPTY) ans++;
        }
    }
    return ans;
}

int main() {
    string line;
    while(getline(cin, line)) {
        cout << solve(line) << endl;
    }   
}
