#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <limits>
using namespace std;

typedef vector<vector<int>> matrix;
constexpr int kInf = numeric_limits<int>::max() / 2;

int sum_range(const vector<int>& accums, int left, int right) {
  if (left > right) return 0;
  int res = accums[right];
  if (left > 0) {
    res -= accums[left - 1];
  }
  return res;
}

int rec(const vector<int>& accums, int left, int right, matrix& dp) {
  if (left > right) return 0;

  if (dp[left][right] == kInf) {
    for (int i=left;i<=right;++i) {
      dp[left][right] = min(
          dp[left][right],
          rec(accums, left, i-1, dp)  + sum_range(accums, left, i-1) +  // Left sub tree.
          rec(accums, i+1, right, dp) + sum_range(accums, i+1 , right));  // Right sub tree.
    }
  }
  return dp[left][right];
}


int solve(const vector<int>& freqs) {
  int n = freqs.size();
  vector<int> accums(n, 0);
  accums[0] = freqs[0];
  for (int i=1;i<n;++i) {
    accums[i] = accums[i-1] + freqs[i];
  }

  matrix dp(n, vector<int>(n, kInf));
  // Initialize
  for (int i=0;i<n;++i) {
    dp[i][i] = 0;
  }

  return rec(accums, 0, n-1, dp);
}

int main() {
  int N;
  while (cin >> N) {
    vector<int> freqs;
    for (int i=0;i<N;++i) {
      int f;
      cin >> f;
      freqs.push_back(f);
    }
    cout << solve(freqs) << endl;
  }
}
