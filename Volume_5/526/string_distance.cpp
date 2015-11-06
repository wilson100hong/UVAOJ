#include <iostream>
#include <string> 
#include <vector>
using namespace std;

int dp[80][80];

#define UNDEF -1
#define INSERT 0
#define DELETE 1
#define REPLACE 2
#define NOP 3
int op[81][81];

int dr[] = {0, -1, -1, -1};
int dc[] = {-1, 0, -1, -1};

void solve(const string& from, const string& to) {
  int R = from.size();
  int C = to.size();
  // initalize dp & op 
  for (int r = 0; r <= R; ++r) {
    for (int c = 0; c <= C; ++c) {
      dp[r][c] = 0;
      op[r][c] = UNDEF;
    }
  }
  
  dp[0][0] = 0;
  op[0][0] = NOP;
  for (int r = 1; r <= R; ++r) {
    dp[r][0] = dp[r - 1][0] + 1;
    op[r][0] = DELETE;
  }
  for (int c = 1; c <= C; ++c) {
    dp[0][c] = dp[0][c - 1] + 1;
    op[0][c] = INSERT;
  }
  for (int r = 1; r <= R; ++r) {
    for (int c = 1; c <= C; ++c) {
      int dist = 100000;
      int cmd = UNDEF;
      bool equal = (from[r - 1] == to[c - 1]);
      int ndist = dp[r - 1][c - 1] + (equal ? 0 : 1);
      if (ndist < dist) {
        dist = ndist;
        cmd = equal ? NOP : REPLACE;
      }
      if (dp[r - 1][c] + 1 < dist) {
        dist = dp[r - 1][c] + 1;
        cmd = DELETE;
      }
      if (dp[r][c - 1] + 1 < dist) {
        dist = dp[r][c - 1] + 1;
        cmd = INSERT;
      }
      dp[r][c] = dist;
      op[r][c] = cmd;
    }
  }

  cout << dp[R][C] << endl;
  vector<string> result;
  int r = R, c = C;
  while (r != 0 || c != 0) {
    int cmd = op[r][c];
    int pr = r + dr[cmd];
    int pc = c + dc[cmd];
    if (cmd == REPLACE) {
      string step = "Replace " + to_string(c) + "," + string(1, to[c - 1]);
      result.push_back(step);
    } else if (cmd == INSERT) {
      string step = "Insert " + to_string(c) + "," + string(1, to[c - 1]);
      result.push_back(step);
    } else if (cmd == DELETE) {
      string step = "Delete " + to_string(c + 1); 
      result.push_back(step);
    }
    r = r + dr[cmd];
    c = c + dc[cmd];
  }
  for (int i = result.size() - 1; i >= 0; --i) {
    cout << result.size() - i << " " << result[i] << endl;
  }
}

int main() {
  string from, to;
  bool first = true;
  while (getline(cin, from)) {
    getline(cin, to);
    if (first) {
      first = false;
    } else {
      cout << endl;
    }
    solve(from, to);
  }
}
