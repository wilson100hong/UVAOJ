#include <iostream>
#include <vector>
using namespace std;

int solve(const string& str) {
  vector<int> table(str.size(), 0);
  // build table: proper prefix
  table[0] = -1;
  table[1] = 0;
  int cursor = 2;
  int anchor = 0;
  while (cursor < str.size()) {
    if (str[anchor] == str[cursor - 1]) {
      table[cursor++] = ++anchor;
    } else if (anchor > 0) {
      anchor = table[anchor];
    } else {  // anchor = 0
      table[cursor++] = 0;
    }
  }

  int end = str.size() - 1;
  if (str[end] != str[table[end]]) return 1;
  int period = end - table[end];
  if (str.size() % period != 0) return 1;
  return str.size() / period;
}

int main() {
  string line;
  while (getline(cin, line)) {
    string str = line;
    if (line == ".") break;
    cout << solve(str) << endl;
  }
}
