#include <iostream>
using namespace std;

string scramble(string s) {
  int len = s.length();
  string s2(s);
  int i = 0;
  while (i < len) {
    if (s[i] == ' ') {
      s2[i] = ' ';
      i++;
    } else {
      int j = i;
      while(j < len && s[j] != ' ') {
        j++;  
      }
      int k = j - 1;
      int l = i;
      while (k >= i) {
        s2[l++] = s[k--];  
      }
      i = j;
    }
  }

  return s2;
}

int main() {
  string line;
  while (getline(cin, line)) {
    cout << scramble(line) << endl;  
  }
  return 0;
}
