#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;

void Solve(const string& x) {
  vector<int> digits;
  for (char c : x) {
    digits.push_back(c - '0');
  }

  sort(digits.begin(), digits.end());

  // Calculate number of 0
  int zc = 0;
  while (zc < digits.size()) {
    if (digits[zc] != 0) break;
    zc++;
  }
  
  // 1. Get a
  ULL a = 0;
  for (int i=digits.size()-1;i>=0;--i) {
    a = a*10 + digits[i];
  }
  
  // 2. Get b
  ULL b = digits[zc];  // since x is positive, must have a non-zero digit
  for (int i=0;i<zc;++i) {
    b *= 10;
  }
  for (int i=zc+1;i<digits.size();++i) {
    b = b*10 + digits[i];
  }

  ULL c = a - b;
  cout << a << " - " << b << " = " << c << " = 9 * " << c / 9 << endl;
}

int main() {
  string x;
  while (getline(cin, x)) {
    Solve(x);
  }
}
