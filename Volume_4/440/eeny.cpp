#include <iostream>
#include <vector>
using namespace std;

int ANS[150];

void init() {
  for (int i=0;i<150;++i) ANS[i] = -1;
  int done = 3;  // ANS[0..2] does not need to be computed.

  // F(n, m) is the solution of Joseph ring.
  // ANS[n] = minimum m satisfy F(n-1, m) == 0 
  for (int m=1;m<1000;++m) {
    int f = 0;  // F(1, m) = 0
    for (int n=2;n<150;++n) {  // n from [2, 149]
      f = (f + m) % n;
      if (f == 0 && ANS[n+1] == -1) {
        ANS[n+1] = m;
        if (done == 150) return;
      }
    }
  }
}

int main() {
  init();
  int n;
  while (cin >> n) {
    if (n == 0) break;
    cout << ANS[n] << endl;
  }
}
