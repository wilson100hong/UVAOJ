#include <iostream>
#include <string>
using namespace std;

typedef unsigned long UL;
int main() {
  UL n;
  while (cin >> n) {
    if (n == 0) break;
    string res = "";
    int prt = 0;
    while (n) {
      if (n & 1) {
        res = "1" + res;
        prt++;
      } else {
        res = "0" + res;
      }
      n = n >> 1;
    }
    cout << "The parity of " << res << " is " << to_string(prt) << " (mod 2)." << endl;
  }
}
