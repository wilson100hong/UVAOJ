#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int solve(const string& str) {
  int size = str.size();
  vector<int> table(size, 0);
  table[0] = -1;
  table[1] = 0;
  int cur = 2, cnd = 0;
  while (cur < size) {
    if (str[cur - 1] == str[cnd]) {
      table[cur++] = ++cnd;
    } else if (cnd > 0) {
      cnd = table[cnd];
    } else {  // cnd == 0
      table[cur++] = 0;
    }
  }
  int end = size - 1;
  if (str[end] != str[table[end]]) return size;
  int period = end - table[end];
  if (size % period != 0) return size;
  return period;
}

int main() {
  string line;
  int n;
  cin >> n;
  getline(cin, line);
  bool first = true;
  while (n--) {
    getline(cin, line);
    getline(cin, line);
    if (first) {
      first = false;
    } else {
      cout << endl;
    }
    cout << solve(line) << endl;
  }
}
