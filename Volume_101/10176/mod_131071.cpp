#include <iostream>
#include <vector>

using namespace std;

// 2016/11/11
// STAR:
// SKILL:
// TRAP:

int NUM = 131071;

vector<int> REMAINS;

void init() {
  long long base = 1;
  for (int i=0;i<10001;++i) {
    REMAINS.push_back(base);
    base = (base*2) % NUM;
  }
}

string solve(const string& str) {
  int base = 0;
  for (int i=0;i<str.size();++i) {
    int j = str.size()-1-i;
    char c = str[j];
    if (c == '1') {
      base = (base + REMAINS[i]) % NUM;
    }
  }
  if (base % NUM == 0) {
    return "YES";
  } else {
    return "NO";
  }
}

int main() {
  init();
  char c;
  string s = "";
  while (cin >> c) {
    if (c == '#') {
      cout << solve(s) << endl;
      s = "";
    } else if (c == '0' || c == '1') {
      s += c;
    }
  }
}
