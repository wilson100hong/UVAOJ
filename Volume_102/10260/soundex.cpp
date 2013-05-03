#include <iostream>
using namespace std;

int decond(char c) {
  if (c=='B' || c=='F' || c=='P' || c=='V')
    return 1;
  if (c=='C' || c=='G' || c=='J' || c=='K'
    || c=='Q' || c=='S' || c=='X' || c=='Z')
    return 2;
  if (c=='D' || c=='T')
    return 3;
  if (c=='L')
    return 4;
  if (c=='M' || c=='N')
    return 5;
  if (c=='R')
    return 6;
  return -1;
}


int main() {
  string line;
  while(getline(cin, line)) {
    int len = line.length();
    int prev = -1;
    for (int i = 0; i < len; ++i) {
      int cur = decond(line[i]);
      if (cur != -1 && cur != prev) {
        cout << cur;
      }
      prev = cur;
    }
    cout << endl;
  }

  return 0;
}
