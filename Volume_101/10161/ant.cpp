#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int n;
  while (cin >> n) {
    if (n == 0)
      break;
    int sq = sqrt(n); 
    int start = (sq*sq == n ? sq : sq + 1);
    int remain = start*start - n;  
    int x = 0, y = 0;
    if (start % 2 == 0) {
      if (remain < start) {
        x = start; y = remain + 1;
      } else {
        x = 2*start-remain- 1;y = start;
      }
    } else {
      if (remain < start) {
        y = start; x = remain + 1; 
      } else {
        y = 2*start-remain-1;x = start;
      }
    }
    cout << x << " " << y << endl;
  }
}
