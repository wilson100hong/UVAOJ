#include <iostream>
#include <sstream>
#include <set>
#include <utility>
#include <vector>
using namespace std;

stringstream& eatline() {
  static stringstream SS;
  SS.clear();
  string line;
  getline(cin, line);
  SS.str(line);
  return SS;
}

int max(int a, int b) {
  return a > b ? a : b;
}

typedef pair<int, int> II;
int solve(const vector<int>& disks, int cap, int buckets) {
  // build onedisk  O(n^3)
  int n = disks.size();
  set<II> sorted;  // time, index

  for (int i = 0; i < n; ++i) {
    sorted.insert(II(disks[i], i));
  }

  vector<vector<int>> onedisk(n, vector<int>(n, 0));

  for (int i = 0; i < n; ++i) {
    for (int j = i; j < n; ++j) {
      int sum = 0;
      int cnt = 0;
      for (II entry : sorted) {
        int index = entry.second;
        if (index < i || index > j)
          continue;
        if (sum + entry.first > cap)
          break;
        sum += entry.first;
        cnt++;
      }
      onedisk[i][j] = cnt;
    }
  }

  // dp
  vector<int> dp(n, 0);
  // init
  for (int i = 0; i < n; ++i) {
    dp[i] = onedisk[0][i];
  }

  for (int k = 2; k <= buckets; ++k) {
    vector<int> temp(n, 0);
    for (int i = 0; i < n; ++i) {
      for (int m = 0; m < i; ++m) {
        temp[i] = max(temp[i], dp[m] + onedisk[m+1][i]);
      }
    }
    for (int i = 0; i < n; ++i) {
      dp[i] = temp[i];
    }
  }
  return dp[n-1];
}

int main() {
  int rounds;
  eatline() >> rounds;
  bool first = true;
  while (rounds--) {
    eatline();  // blank line
    int n, t, m;
    eatline() >> n >> t >> m;
    stringstream& ss = eatline();
    vector<int> disks;
    for (int i = 0; i < n; ++i) {
      int ti;
      char dummy;
      if (i > 0) 
        ss >> dummy;
      ss >> ti;
      disks.push_back(ti);
    }
    if (!first) {
      cout << endl;
    }
    cout << solve(disks, t, m) << endl;
    first = false;
  }
}
