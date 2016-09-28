// 2016/09/28
// STARS: *
// SKILLS: dp, graph
// trap: ans >= 0
#include <iostream>
#include <vector>
#include <set>
#include <limits>

using namespace std;

#define MIN numeric_limits<int>::min()

struct State {
  bool done;
  int value;
};

int search(const vector<vector<int>>& cities, 
    vector<vector<State>>& dp, int cur, int inters) {
  if (dp[cur][inters].done) {
    return dp[cur][inters].value;
  }
  dp[cur][inters] = {true, MIN};
  for (int to=0;to<cities.size();++to) {
    if (to == cur) continue;
    int revenue = cities[cur][to] + search(cities, dp, to, inters-1);
    if (revenue > dp[cur][inters].value) {
      dp[cur][inters].value = revenue;
    }
  }
  dp[cur][inters].done = true;
  return dp[cur][inters].value;
}

int solve(const vector<vector<int>>& cities, int start,
    const set<int>& ends, int inters) {
  vector<vector<State>> dp(cities.size(), vector<State>(inters+1, {false, 0}));
  for (int i=0;i<cities.size();++i) {
    if (ends.count(i)) {
      dp[i][0] = {true, 0};
    } else {
      dp[i][0] = {true, MIN};  // should be negative
    }
  }
  int ans = search(cities, dp, start, inters);
  return ans > 0 ? ans : 0;
}

int main() {
  // cout << MIN << endl;
  int C, S, E, T;
  while (cin >> C >> S >> E >> T) {
    if (C==0 && S==0 && E==0 && T==0) 
      break;
    vector<vector<int>> cities(C, vector<int>(C, 0));
    for (int i=0;i<C;++i) {
      for (int j=0;j<C;++j) {
        cin >> cities[i][j];
      }
    }
    set<int> ends;
    for (int i=0;i<E;++i) {
      int e;
      cin >> e;
      ends.insert(e-1);  // 0-based!
    }
    cout << solve(cities, S-1 /* 0-based */, ends, T) << endl;
  }
}
