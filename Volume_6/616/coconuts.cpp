// 1. 3 coconuts is a special case, so persons need to start from sqrt(n) + 1
// 2. the problem want largest number of people
#include <iostream>
#include <math.h>
using namespace std;

typedef long long int LL;

void solve(LL n) {
  cout << n << " coconuts, ";
  for (int persons = sqrt(n) + 1; persons >= 2; --persons) {
    int m = n;
    bool success = true;
    for (int i = 0; i < persons; ++i) {  // all person
      m--;
      if (m % persons != 0 || m < 0) {
        success = false;
        break;
      } else {
        m -= (m / persons);
      }
    }
    if (success && m % persons == 0) {
      cout << persons << " people and 1 monkey" << endl;
      return;
    }
  }
  cout << "no solution" << endl;
}


int main() {
  LL n;
  while (1) {
    cin >> n;
    if (n < 0) break;
    solve(n);
  }
}
