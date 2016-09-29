// wA!
// 2016/09/29
// STARS: *
// SKILL: dp
// trap: 1. use static array to save some time
//       2. unsigned long int 
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
  int zero;
  int one;
  bool special;
};

#define MAX_N 26
Vertex GRAPH[MAX_N];
int N=0, M=0;

struct State {
  unsigned long int ways;
  bool done;
};

unsigned long int search(vector<vector<State>>& dp, int cur, int moves) {
  if (dp[moves][cur].done) {
    return dp[moves][cur].ways;
  }
  dp[moves][cur] = {
    search(dp, GRAPH[cur].zero, moves-1) + search(dp, GRAPH[cur].one, moves-1),
    true};
  return dp[moves][cur].ways;
}

unsigned long int solve() {
  // dp[m][v]: the number of ways from v to a special nodes,
  // using m moves
  vector<vector<State>> dp(1+M, vector<State>(N, {0, false}));
  for (int i=0;i<N;++i) {
    if (GRAPH[i].special) {
      dp[0][i] = {1, true};
    } else {
      dp[0][i] = {0, true};
    }
  }
  return search(dp, 0, M);
}

int main() {
  while (cin >> N) {
    char a, b, c, d;
    for (int n=0;n<N;++n) {
      cin >> a >> b >> c >> d;
      GRAPH[a-'A'] = {b-'A', c-'A', d =='x'};
    }
    cin >> M;
    cout << solve() << endl;
  }
}
