// 2016/10/01
// STAR: *
// SKILL: recursive
// TRAP: the input format on website is wrong!
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

void dump(vector<bool>& board) {
  for (int r=0;r<8;++r) {
    for (int c=0;c<8;++c) {
      cout << board[8*r+c] << " ";
    }
    cout << endl;
  }
}


void place(vector<bool>& board, int r, int c) {
  // whole row
  for (int r=0;r<8;++r) {
    board[8*r+c] = false;
  }
  // whole row
  for (int c=0;c<8;++c) {
    board[8*r+c] = false;
  }
  // diagonals
  int k1 = r-c, k2 = r+c;
  for (int c=0;c<8;++c) {
    int nr = k1+c;
    if (0<= nr && nr < 8) {
      board[8*nr+c] = false;
    }
    nr = k2-c;
    if (0<= nr && nr < 8) {
      board[8*nr+c] = false;
    }
  }
}

void rec(vector<int>& loc,
         vector<bool>& board,
         int col,
         int& sol) {
  if (col == 8) {
    cout << setw(2);
    cout << sol;  // padding
    cout << "     ";
    for (int i=0;i<8;++i) {
      cout << " " << loc[i]+1;
    }
    cout << endl;
    sol++;
    return;
  }

  if (loc[col] != -1) {
    rec(loc, board, col+1, sol);
  } else {
    for (int row=0;row<8;++row) {
      if (board[8*row+col]) {
        vector<bool> nb = board;
        place(nb, row, col);
        vector<int> nloc = loc;
        nloc[col] = row;
        rec(nloc, nb, col+1, sol);
      }
    }
  }
}


void solve(int r, int c) {
  cout << "SOLN       COLUMN" << endl;
  cout << " #      1 2 3 4 5 6 7 8" << endl;
  cout << endl;
  
  vector<int> loc(8, -1);
  loc[c] = r;
  vector<bool> board(64, true);
  place(board, r, c);
  //dump(board);
  int sol = 1;
  rec(loc, board, 0, sol);
}

int main() {
  int cases;
  cin >> cases;
  bool first = true;
  while (cases--) {
    int R, C;
    cin >> R >> C;
    R--; C--;
    if (!first) {
      cout << endl;
    }
    solve(R, C);
    first = false;
  }
}
