// O(N^3) solution
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

int solve(const vector<int>& numbers) {
  int n = numbers.size();
  // dp[i][j] means the max diff can produce for number[i....j], in either direction
  vector<vector<int>> dp(n, vector<int>(n, -1));
  for (int i = 0; i < n; ++i) {
    dp[i][i] = numbers[i];
  }
  for (int k = 1; k < n; ++k) {
    for (int i = 0; i < n - k; ++i) {
      int j = i + k;
      // cout << "i: " << i << " j: " << j << endl;
      int total = sum(numbers, i, j);  // default select all
      dp[i][j] = total;

      int temp = total - numbers[j];
      for (int m = j -1; m >= i; --m) {
        // pick numbers[i] to numbers[m], m < j
        int cur = temp - dp[m+1][j];
        if (cur > dp[i][j])
          dp[i][j] = cur;
        temp -= numbers[m];
      }

      temp = total - numbers[i];
      for (int m = i + 1; m <= j; ++m) {
        // pick numbers[m] to numbers[j], m > i
        int cur = temp - dp[i][m-1];
        if (cur > dp[i][j])
          dp[i][j] = cur;
        temp -= numbers[m];
      }
    }
  }
  return dp[0][n-1];
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
