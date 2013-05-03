#include <iostream>
using namespace std;

bool all(string s, string t) {
  int i = 0, j = 0;
  while (j < t.length()) {
    if (s[i] == t[j]) {
      i++;
      if (i == s.length()) {
        break;  
      }
    }
    j++;
  }
  return i == s.length();  
}

int main() {
  string s, t;
  while (cin >> s >> t) {
    bool y = all(s, t);
    cout << (y == true ? "Yes" : "No") << endl;
  }
}
