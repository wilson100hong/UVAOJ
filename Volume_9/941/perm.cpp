#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

typedef unsigned long long int ULL;
#define MAX 20
vector<ULL> factorials;

// initialize factorials to 19!
void init() {
  ULL fac = 1;
  factorials.push_back(1);  // 0! = 1
  for (int i = 1; i < 20; ++i) {
    fac *= i;
    factorials.push_back(fac);
  }
}

ULL s2i(const string& str) {
  stringstream ss(str);
  ULL n;
  ss >> n;
  return n;
}

char get_symbol(const string& symbols, vector<bool>& used, int nth) {
  int index = 0;
  while (used[index]) index++;
  while (nth > 0) {
    index++;
    if (!used[index]) {
      nth--;
    }
  }
  used[index] = true;
  return symbols[index];
}

string solve(string symbols, ULL order) {
  // sort symbols
  sort(symbols.begin(), symbols.end());
  int n = symbols.size();
  vector<bool> used(n, false);
  string result(n ,'A');
  for (int i = 0; i < n; ++i) {
    ULL base = factorials[n-1-i];
    result[i] =  get_symbol(symbols, used, order / base);
    order %= base;
  }
  return result;
}

int main() {
  init();
  string line;
  getline(cin, line);
  ULL round = s2i(line);
  while (round-- > 0) {
    string symbols;
    getline(cin, symbols);
    getline(cin, line);
    cout << solve(symbols, s2i(line)) << endl;
  }
}
