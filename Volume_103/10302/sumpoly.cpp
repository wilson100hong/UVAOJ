#include <iostream>
using namespace std;

int main () {
  int n;
  while (cin >> n) {
    unsigned long long int x = n;
    x = x * (x + 1);
    x /= 2;
    x *= x;
    cout << x << endl;
  }
  return 0;
}
