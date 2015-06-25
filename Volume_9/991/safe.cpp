//
// Catalan Number
//
#include <iostream>

using namespace std;
int CATALAN[11] = {0};

void init() {
  CATALAN[0] = 1;
  CATALAN[1] = 1;
  for (int i = 2; i < 11; ++i) {
    for (int j = 0; j < i; ++j) {
      CATALAN[i] += CATALAN[j] * CATALAN[i - j - 1];
    }
  }
}

int main() {
  init();
  int n;
  bool first = true;
  while (cin >> n) {
    if (!first) {
      cout << endl;
    }
    first = false;
    cout << CATALAN[n] << endl;
  }
}
