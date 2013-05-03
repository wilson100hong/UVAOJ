#include <iostream>
using namespace std;
int bigmod(int b, int p, int m) {
  b %= m;
  int cur = 1;
  int base = b;
  while (p != 0) {
    if (p & 1) {
      cur = cur * base;
      cur %= m;
    }
    base = (base * base) % m; 
    p = p>> 1;
  }
  return cur;
}

int main() {
  int b, p, m;
  while (cin >> b >> p >> m) {
    cout << bigmod(b, p, m) << endl;      
  }
}
