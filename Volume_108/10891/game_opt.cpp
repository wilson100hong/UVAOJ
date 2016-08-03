// O(N^2) solution
#include <iostream>
#include <vector>
using namespace std;

int sum(const vector<int>& numbers, int s, int t) {
  int res = 0;
  for (int i = s; i <= t; ++i) {
    res += numbers[i];
  }
  return res;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int max(const vector<int> v) {
  int res = v[0];
  for (int e : v) {
    res = max(res, e);
  }
  return res;
}

int solve(const vector<int>& numbers) {
  int n = numbers.size();
  // dp[i][j] means the max diff the play can cause, picking from i to j.
  // when i < j, pick from left to right. when i > j, right to left
  vector<vector<int>> dp(n, vector<int>(n, -1));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = numbers[i];
  }

  for (int k = 1; k < n; ++k) {
    // 1. upper triangle
    for (int i = 0; i < n - k; ++i) {
      int j = i + k;
      // enemy's best move
      int enemy = max(dp[i+1][j], dp[j][i+1]);
      dp[i][j] = max(numbers[i] - enemy, numbers[i] + dp[i+1][j]);
    }
    // 2. lower triangle
    for (int j = 0; j < n - k; ++j) {
      int i = j + k;
      int enemy = max(dp[j][i-1], dp[i-1][j]);
      dp[i][j] = max(numbers[i] - enemy, numbers[i] + dp[i-1][j]);
    }
  }
  return max(dp[0][n-1], dp[n-1][0]);
}

int main() {
  int n;
  while (cin >> n) {
    if (n == 0) break;
    vector<int> numbers;
    for (int i = 0; i < n; ++i) {
      int num;
      cin >> num;
      numbers.push_back(num);
    }
    cout << solve(numbers) << endl;
  }
}
