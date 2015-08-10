#include <iostream>
using namespace std;
#define MAX 102

int main() {
  int count[MAX];
  while (1) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    for (int i = 0; i < MAX; ++i) {
      count[i] = 0;
    }
    while (n-- > 0) {
      int age;
      cin >> age;
      count[age]++;
    }

    bool first = true;
    for (int i = 0; i < MAX; ++i) {
      for (int j = 0; j < count[i]; ++j) {
        if (first) {
          first = false;
        } else {
          cout << " ";
        }
        cout << i;
      }
    }
    cout << endl;
  }
}
