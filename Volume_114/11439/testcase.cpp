// Generate random test cases
#include <iostream>
#include <stdlib.h>
using namespace std;

#define W  3
#define MAX 20
int main() {
  int N = 1 << W;
  for (int n = 0; n < N - 1; ++n) {
    bool first = true;
    for (int m = n + 1; m < N; ++m) {
      if (first) {
        first = false;
      } else {
        cout << " ";
      }
      cout << rand() % MAX + 1;
    }
    cout << endl;
  }
}
