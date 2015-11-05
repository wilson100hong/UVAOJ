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
  if (table[end] == 0) {
    return 1;
  } else {
    int len = (end - table[end]);
    return end / (end - table[end]);
  }
}

int main() {
  string line;
  while (getline(cin, line)) {
    string str = line + line[0];
    if (line == ".") break;
    cout << solve(str) << endl;
  }
}
