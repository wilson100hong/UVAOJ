#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
  int N = 1 << 3;
  for (int n = 0; n < N - 1; ++n) {
    bool first = true;
    for (int m = n + 1; m < N; ++m) {
      if (first) {
        first = false;
      } else {
        cout << " ";
      }
      cout << rand() % 20 + 1;
    }
    cout << endl;
  }
}
