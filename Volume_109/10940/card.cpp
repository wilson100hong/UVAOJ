#include <iostream>
using namespace std;

#define MAX 500000 + 1
int dp[MAX];

void init() {
  // 1-based index!
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 2; i < MAX; ++i) {
    dp[i] = dp[i - 1] + 2;
    if (dp[i] > i) {
      dp[i] = 2;
    }
  }
}

int main() {
  int n;
  init();
  while (1) {
    cin >> n;
    if (n == 0) break;
    cout << dp[n] << endl;
  }
}
