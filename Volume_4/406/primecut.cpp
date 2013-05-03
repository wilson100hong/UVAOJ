#include <iostream>
using namespace std;
#define N 1001
bool prime[N];
int pn[N];
int pc;
void init() {
  for (int i = 0; i < N; ++i)
    prime[i] = true;
  prime[0] = false;
  prime[1] = true;
  pn[0] = 1, pc = 1;
  for (int i = 2; i < N; ++i) {
    if (prime[i]) {
      pn[pc++] = i;
      int j = 2*i;
      while (j < N) {
        prime[j] = false;
        j += i;
      }
    }
  }
}

// todo: maybe use BS
int bound(int n) {
  int b = 0;
  while (pn[b] <= n && b < pc)
    b++;
  return b;
}

int min (int a, int b) {
  return a < b ? a : b;
}
int max(int a, int b) {
  return a >= b ? a : b;
}

int main () {
  init();
  int n, c;
  while (cin >> n >> c) {
    cout << n << " " << c << ":";
    int b = bound(n);
    int m = b / 2;
    int start = (b % 2 ==0) ? m - c: m - c + 1; 
    start = max(0, start);
    int end = min(b, m + c);
    
    for (int i = start; i < end; ++i)
      cout << " " << pn[i];
    cout << endl << endl;
  }
  return 0;
}
