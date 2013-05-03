#include <iostream>
using namespace std;

int min(int a, int b) {
  return a < b ? a : b;
}
int main() {
  string line1;
  int cnt1[26], cnt2[26];
  while (getline(cin, line1)) {
    string line2;
    getline(cin, line2);
    for (int i = 0; i < 26; ++i) {
      cnt1[i] = cnt2[i] = 0;
    }
    for (int i =0; i <line1.length(); ++i) {
      char c = line1[i];
      cnt1[(int) (c - 'a')]++;
    }
    for (int i =0; i <line2.length(); ++i) {
      char c = line2[i];
      cnt2[(int) (c - 'a')]++;
    }

    for (int i =0;i < 26; ++i) {
      int cnt = min(cnt1[i], cnt2[i]);
      while (cnt-- > 0) 
        cout << (char) (i + 'a');
    }
    cout << endl;
  }

  return 0;
}
