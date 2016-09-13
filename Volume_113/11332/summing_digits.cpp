#include <iostream>
using namespace std;

typedef unsigned long int UL;

UL f(UL n) {
  UL res = 0;
  while (n > 0) {
    res += (n % 10);
    n /= 10;
  }
  return res;
}

UL g(UL n) {
  while (n >= 10) {
    n = f(n);
  }
  return n;
}

int main() {
  UL n;
  while (cin >> n) {
    if (n == 0) break;
    cout << g(n) << endl;
  }
}
