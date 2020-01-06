#include <iostream>
using namespace std;

typedef unsigned long long ULL;

ULL Next(ULL x) {
  ULL y = x*x;
  return (y % 1000000) / 100;
}

ULL Solve(ULL x) {
  ULL a = x, b = x;
  int step = 0;
  while (1) {
    a = Next(a);
    b = Next(Next(b));
    step++;
    if (a == b) break;
  }
  // 1. Find cycle length.
  int cycle_len = 0;
  do {
    b = Next(b);
    cycle_len++;
  } while (a != b);

  // 2. Find x to start of cycle.
  int total_len = 0;
  b = x;
  while (b != a) {
    b = Next(b);
    total_len++;
  }

  b = x;
  int back = cycle_len - (total_len % cycle_len); // backtrace for total_len
  while (back--) {
    a = Next(a);
  }
  
  int offset_len = 0;
  while (a != b) {
    a = Next(a);
    b = Next(b);
    offset_len++;
  }
  return offset_len + cycle_len;
}

int main() {
  ULL x;
  while (cin >> x) {
    if (x == 0) break;
    cout << Solve(x) << endl;
  }
}

