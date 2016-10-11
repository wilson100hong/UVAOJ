#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// 2016/10/11
// STAR: 
// SKILL: dp, brain teaser
// TRAP: overflow

unsigned long long DP[51];


void init() {
  DP[1] = 1;
  DP[2] = 2;
  for (int n=3;n<=50;++n) {
    DP[n] = DP[n-1] + DP[n-2];
  }
}

int main() {
  init();
  int n;
  while (cin >> n) {
    if (n == 0) break;
    cout << DP[n] << endl;
  }
}
