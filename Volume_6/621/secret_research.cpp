#include <iostream>
using namespace std;

char solve(const string& str) {
  int n = str.size();
  if (str=="1" || str=="4" || str=="78") return '+';
  if (n >= 2 && str.substr(n-2) == "35") return '-';
  if (n >= 2 && str[0] == '9' && str[n-1] == '4') return '*';
  if (n >= 3 && str.substr(0, 3) == "190") return '?';
  return '?';
}

int main() {
  int n;
  cin >>n;
  string line;
  getline(cin, line);

  while (n--) {
    getline(cin, line);
    cout << solve(line) << endl;
  }
}
