// 1. dp[][] array can be unsigned long long!
// 2. watch out negative mod 
// 3. watch out the order of dp[][] update: the iterator m is from bottom to top.
#include <iostream>
#include <vector>
using namespace std;

#define MAX_M 11
#define MAX_D 20

typedef unsigned long long int ULL;
ULL dp[MAX_M][MAX_D];

void init() {
  for (int m = 0; m < MAX_M; ++m)
    for (int d = 0; d < MAX_D; ++d)
      dp[m][d] = 0;
  dp[0][0] = 1;  // there is alwasy one way to do that.
}

int min(int a, int b) {
  return a < b ? a : b;
}

int mod(long int num, int D) {
  if (num < 0) {
    long long int nn = num * -1;
    return D - (nn % D);
  } else {
    return num % D;
  }
}

ULL solve(const vector<long int>& numbers, int D, int M) {
  init();
  for (int i = 0; i < numbers.size(); ++i) {
    int num = mod(numbers[i], D); 
    // reverse order of m
    for (int m = min(i + 1, M); m > 0; --m) {
      for (int d = 0; d < D; ++d) {
        int x = (d + D - num) % D;
        dp[m][d] += dp[m - 1][x];
      }
    }
  }
  return dp[M][0];
}

int main() {
  int N, Q;
  int round = 1;
  while (1) {
    cin >> N >> Q;
    if (N == 0 && Q == 0) break;
    vector<long int> numbers;
    for (int i = 0; i < N; ++i) {
      long int num;
      cin >> num;
      numbers.push_back(num);
    }
    cout << "SET " << round++ << ":" << endl;
    for (int i = 1; i <= Q; ++i) {
      int D, M;
      cin >> D >> M;
      cout << "QUERY " << i << ": " << solve(numbers, D, M) << endl;
    }
  }
}
