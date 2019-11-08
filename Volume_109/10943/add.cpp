#include <iostream>
#include <vector>
using namespace std;

int DP[101][101];
constexpr int kUndef = -1;

void init() {
  for (int i=0;i<101;++i) {
    DP[i][0] = 0;
    DP[i][1] = 1;
    for (int j=2;j<101;++j) {
      DP[i][j] = kUndef;
    }
  }
}

int solve(int N, int K) {
  if (DP[N][K] == kUndef) {
    DP[N][K] = 0;
    for (int n=0;n<=N;++n) {
      DP[N][K] = (DP[N][K] + solve(N-n, K-1)) % 1000000;
    }
  }
  return DP[N][K];
}

int main() {
  init();
  int N, K;
  while (cin >> N >> K) {
    if (N == 0 && K == 0) break;
    cout << solve(N, K) << endl;

  }
}
