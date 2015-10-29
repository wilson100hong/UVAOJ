#include <iostream>
using namespace std;

int s2i(const string& s) {
  int res = 0;
  for (int i = 0; i < s.size(); ++i) {
    res *= 10;
    res += (s[i] - '0');
  }
  return res;
}

int math(int a, int b, char op) {
  if (op == '+') return a + b;
  if (op == '-') return a - b;
  return -1;
}

int validate(const string& str) {
  int cur = 0;
  while (str[cur] != '+' &&
         str[cur] != '-' &&
         cur < str.size()) {
    cur++;
  }
  string a = str.substr(0, cur);
  char op = str[cur];
  int last = ++cur;
  while (str[cur] != '=' &&
         cur < str.size()) {
    cur++;
  }
  string b = str.substr(last, cur - last);
  last = ++cur;
  string c = str.substr(last, str.size() - last);
  if (c == "?") return 0;
  return math(s2i(a), s2i(b), op) == s2i(c);
}

int main() {
  string line;
  int score = 0;
  while (getline(cin, line)) {
    score += validate(line);
  }
  cout << score << endl;
}
