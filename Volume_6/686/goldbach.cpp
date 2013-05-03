#include <iostream>
#include <cmath>

using namespace std;
#define MAX_N 40000
bool prime[MAX_N];
void init() {
  for (int i = 0; i < MAX_N; ++i)
    prime[i] = true;
  int s = 2;
  int n = sqrt(MAX_N);
  while (s <= n) {
    if (prime[s]) {
      int t = 2 * s;
      while (t < MAX_N) {
        prime[t] = false;
        t += s;
      }
    }
    s++;
  }
}
int main() {
  init();
  int n;
  while (cin >> n) {
    if (n == 0)
      break;
    
    int t = 2;
    int cnt = 0;
    while (t <= n / 2) {
      if (prime[t] && prime[n - t])
        cnt++;
      t++;
    }
    cout << cnt << endl;
  }
  
  return 0;
}
