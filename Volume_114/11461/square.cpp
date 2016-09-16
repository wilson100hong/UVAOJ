#include <iostream>
using namespace std;

int solve(int a, int b) {
  int cnt = 0;
  int cur=1;
  while (true) {
    int sq = cur*cur;
    if (a<=sq && sq<=b) {
      cnt++;
    }
    if (sq>b) break;
    cur++;
  }
  return cnt;
}

int main() {
  int a, b;
  while (1) {
    cin >> a >> b;
    if (a==0 && b==0) break;
    cout << solve(a, b) << endl;
  }
}

