#include <iostream>
using namespace std;
typedef unsigned long int UL;

UL max(UL a, UL b) {
  return a > b ? a : b;
}

void swap(UL& a, UL& b) {
  UL tmp = a;
  a = b;
  b = tmp;
}

int main() {
  UL a, b, c;
  while (1) {
    cin >> a >> b >> c;
    if (a == 0 && b == 0 && c == 0) {
      break;
    }
    if (b > a) {
      swap(a, b);
    }
    if (c > a) {
      swap(a, c);
    }
    bool right = (a*a == b*b + c*c);
    if (right) {
      cout << "right" << endl;
    } else {
      cout << "wrong" << endl;
    }
  }
}
