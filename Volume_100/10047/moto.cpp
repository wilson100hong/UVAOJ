// BUG: you can' turn and forward at the same time
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define INF 10000000  // TODO: make sure its safe!

enum COLOR {
  GREEN = 0,
  BLACK = 1,
  RED = 2,
  BLUE = 3,
  WHITE = 4,
  NUM_COLOR =5
};

enum DIRECTION {
  NORTH = 0,
  EAST,
  SOUTH,
  WEST,
  NUM_DIRECTION
};

// N -> E -> S -> W
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

struct State {
  COLOR color;
  DIRECTION dir;
  int row;
  int col;
  int spent;
};

typedef vector<vector<int>> Matrix;
typedef vector<int> Row;

#define PATH 0
#define WALL 1

int main() {
  int row, col;
  int sr, sc, er, ec;  // start and end
  int tc = 1;
  while (1) {
    cin >> row >> col;
    if (row == 0 && col == 0) break;
    Matrix field(row, Row(col, WALL));
    for (int r = 0; r < row; ++r) {
      for (int c = 0; c < col; ++c) {
        char x;
        cin >> x;
        if (x == '.' || x == 'S' || x == 'T') {
          field[r][c] = PATH;
          if (x == 'S') {
            sr = r; sc = c;
          } else if (x == 'T') {
            er = r; ec = c;
          }
        }
      }
    }

    // initalize dp array (4D!)
    vector<vector<Matrix>> dp;
    for (int color = GREEN; color < NUM_COLOR; ++color) {
      dp.push_back(
          vector<Matrix>(NUM_DIRECTION,
              Matrix(row, Row(col, INF))));
    }

    // BFS
    queue<State> Q;
    Q.push({GREEN, NORTH, sr, sc, 0});

    bool success = false;
    int spent = 0;
    while (!Q.empty()) {
      State state = Q.front();  Q.pop();
      if (dp[state.color][state.dir][state.row][state.col] > state.spent) {
        dp[state.color][state.dir][state.row][state.col] = state.spent;
      }
      // hit endpoint with correct color
      if (state.row == er && state.col == ec && state.color == GREEN) {
        success = true;
        spent = state.spent;
        break;
      }
      // 1. left & right
      for (int dd = -1; dd <= 1; dd += 2) {
        DIRECTION next_dir = static_cast<DIRECTION>((static_cast<int>(state.dir) + dd + NUM_DIRECTION) % NUM_DIRECTION);
        State next = {state.color, next_dir, state.row, state.col, state.spent + 1};
        if (dp[state.color][next_dir][state.row][state.col] > next.spent) {
          Q.push(next);
        }
      }
      // 2. forward
      int next_row = state.row + dr[state.dir], next_col = state.col + dc[state.dir];
      COLOR next_color = static_cast<COLOR>((static_cast<int>(state.color) + 1) % NUM_COLOR);
      State next = {next_color, state.dir, next_row, next_col, state.spent + 1};
      if (0 <= next_row && next_row < row &&
          0 <= next_col && next_col < col &&
          field[next_row][next_col] == PATH && dp[next_color][state.dir][next_row][next_col] > next.spent) {
        Q.push(next);
      }
    }

    if (tc > 1)  cout << endl;
    cout << "Case #" << tc++ << endl;
    if (success) {
      cout << "minimum time = " << spent << " sec" << endl;
    } else {
      cout << "destination not reachable" << endl;
    }
  }
}
