#include <iostream>
using namespace std;
int main() {
  string s;
  while (cin >> s) {
    if (s == "0") {
      break;
    }
    int sum = 0;
    int len = s.length();
    for (int i = 0; i < len; ++i) {
      int d = (int) (s[i] - '0');
      sum += d * ((1 << (len - i)) - 1);
    }
    cout << sum << endl; 
    //cout << s[0] << endl;
    //cout << s << endl;
  }
  return 0;
}
