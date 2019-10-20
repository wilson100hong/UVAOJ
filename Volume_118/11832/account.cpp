#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX_VAL 40000
#define MAX_COL MAX_VAL * 2 + 1

#define PLUS 1
#define MINUS 2

// Value to index
int v2i(int v) {
  return v + MAX_VAL;
}

int i2v(int i) {
  return i - MAX_VAL;
}

string solve(const vector<int>& trans, int F) {
  int N = trans.size();

  vector<vector<int>> dp(N, vector<int>(MAX_COL, 0));

  // 0: no way
  // 1: +
  // 2: -
  // 3: both
  
  // First row
  dp[0][v2i(trans[0])] = PLUS;
  dp[0][v2i(-trans[0])] = MINUS;

  for (int i=1;i<N;++i) {
    for (int j=0;j<MAX_COL;++j) {
      if (dp[i-1][j] == 0) continue;

      int v = i2v(j);

      int vp = v + trans[i];
      if (vp <= MAX_VAL) {
        dp[i][v2i(vp)] += PLUS;
      }
      int vm = v - trans[i];
      if (-MAX_VAL <= vm) {
        dp[i][v2i(vm)] += MINUS;
      }
    }
  }

  if (dp[N-1][v2i(F)] == 0) {
    return "*";
  }

  vector<char> ans(N, '.');

  set<int> search_value = {F};

  for (int i=N-1;i>=0;--i) {
    set<int> next_search_value;
    bool plus = false;
    bool minus = false;

    for (int f : search_value) {
      int w = dp[i][v2i(f)];
      if (w & PLUS) {
        plus = true;
        next_search_value.insert(f - trans[i]);
      }
      if (w & MINUS) {
        minus = true;
        next_search_value.insert(f + trans[i]);
      }
    }

    if (plus && !minus) {
      ans[i] = '+';
    } else if (!plus && minus) {
      ans[i] = '-';
    } else {
      ans[i] = '?';
    }
    search_value = next_search_value;
  }
  return string(ans.begin(), ans.end());
}

int main() {
  int N, F;
  while (cin >> N >> F) {
    if (N == 0 && F == 0) break;

    vector<int> trans;
    int x;
    for (int i=0;i<N;++i) {
      cin >> x;
      trans.push_back(x);
    }
    cout << solve(trans, F) << endl;
  }
}
