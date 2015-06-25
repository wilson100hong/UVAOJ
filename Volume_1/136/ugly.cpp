#include <iostream>
#include <vector>
using namespace std;

int min(int a, int b) {
  return a < b ? a : b;  
}

int TH = 1500;
int main() {
  vector<int> sol(TH, 0);
  sol[0] = 1;
  int n = 0;
  while (n < TH - 1) {
    int cur = sol[n];
    int i, j, k = 0;
    
    for (i = 0; sol[i] * 2 <= cur; ++i) {
    ;
    }
    for (j = 0; sol[j] * 3 <= cur; ++j) {
    ;
    }
    for (k = 0; sol[k] * 5 <= cur; ++k) {
    ;
    }

    sol[++n] = min(sol[i]*2, min(sol[j]*3, sol[k]*5));
  }
  cout << "The 1500'th ugly number is " << sol[TH - 1] << "." << endl;
}
