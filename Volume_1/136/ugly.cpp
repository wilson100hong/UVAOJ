#include <iostream>
using namespace std;
int min(int a, int b) {
  return a < b ? a : b;  
}
int main() {
  int th = 1500;
  int* sol= new int[th];
  sol[0] = 1;
  int n = 0;
  while (n < th - 1) {
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

    int solution = min(sol[i]*2, min(sol[j]*3, sol[k]*5));
    sol[n + 1] = solution;
    n++;
  }
  cout << "The 1500'th ugly number is " << sol[th-1] << "." << endl;
  delete sol;
}
