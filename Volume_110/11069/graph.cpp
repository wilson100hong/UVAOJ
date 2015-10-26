#include <iostream>
using namespace std;
int dp[77];  // 0 ~ 76

void init() {
  dp[1] = 1;
  dp[2] = 2;
  dp[3] = 2;
  for (int i = 4; i < 77; ++i) {
    dp[i] = dp[i-2] + dp[i-3];
  }
}

int main() {
  int n;
  init();
  while (cin >> n) {
    cout << dp[n] << endl;
  }
}
