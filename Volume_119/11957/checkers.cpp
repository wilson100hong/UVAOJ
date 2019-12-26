#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <limits>
#include <sstream>
#include <iomanip>
#include <queue>

using namespace std;

typedef unsigned long long ULL;

struct Cell {
  int r;
  int c;
};

inline bool InRnage(int N, const Cell& c) {
  return 0 <= c.r && c.r < N &&
         0 <= c.c && c.c < N;
}

void Update(const vector<vector<char>>& table, 
  vector<vector<ULL>>& dp, const Cell& curr, bool dir) {
  const ULL d = dp[curr.r][curr.c];
  if (d <= 0) return;
  const int N = table.size();
  const int dr = -1;
  const int dc = dir ? 1 : -1;
  const Cell next = {curr.r + dr, curr.c + dc};
  if (InRnage(N, next)) {
    const char nx = table[next.r][next.c];
    if (nx == '.') {
      dp[next.r][next.c] = (dp[next.r][next.c] + d) % 1000007;
    } else if (nx == 'B') {
      Cell next2 = {curr.r + 2*dr, curr.c + 2*dc};
      if (InRnage(N, next2) && table[next2.r][next2.c] == '.') {
        dp[next2.r][next2.c] = (dp[next2.r][next2.c] + d) % 1000007;
      }
    }
  }
}


ULL Solve(const vector<vector<char>>& table, pair<int, int>& start) {
  const int N = table.size();
  vector<vector<ULL>> dp(N, vector<ULL>(N, 0));
  dp[start.first][start.second] = 1;

  for (int r=start.first;r>0;--r) {
    for (int c=0;c<N;++c) {
      Update(table, dp, {r, c}, true);
      Update(table, dp, {r, c}, false);
    }
  }

  ULL sum = 0;
  for (int c=0;c<N;++c) {
    sum = (sum + dp[0][c]) % 1000007;
  }
  return sum;
}

int main() {
  int TC;
  cin >> TC;
  for (int tc=1;tc<=TC;++tc) {
    int N;
    cin >> N;
    vector<vector<char>> table(N, vector<char>(N, '.'));
    pair<int, int> start;
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j) {
        cin >> table[i][j];
        if (table[i][j] == 'W') {
          start = {i, j};
        }
      }
    }

    cout << "Case " << tc << ": " << Solve(table, start) << endl;
  }
}
