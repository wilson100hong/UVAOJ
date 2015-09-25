// 1. integer too small, use long long int
// 2. be care of 1-based index with 0-based index in counting offset
#include <iostream>
using namespace std;

typedef long long int LI;

int find_digit(LI number, int offset) {
  while (offset-- > 0) {
    number /= 10;
  }
  return number % 10;
}

int solve(LI n) {
  if (n < 10) return n;
  n -= 9;  // 1-baed index

  int digit = 2;
  LI left = 10, right = 100;
  while (1) {
    LI size = right - left;
    LI len = digit * size;
    if (len >= n) {
      break;
    }
    n -= len;  // n > len
    left *= 10;
    right *= 10;
    digit++;
  }

  LI x = left + (n - 1) / digit;
  LI offset = digit - ( (n - 1) % digit) - 1;  // offset from LSB, 0-based
  return find_digit(x, offset);
}


int main() {
  LI n;
  while (cin >> n) {
    cout << solve(n) << endl;
  }
}
