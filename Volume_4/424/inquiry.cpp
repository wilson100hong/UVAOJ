#include <iostream>
using namespace std;

int max(int a, int b) {
  return a >= b ? a : b;  
}

string sum(string a, string b) {
  int la = a.length();
  int lb = b.length();
  int ls = max(la, lb) + 1;
  char* s = new char[ls];
  int da, db, dc = 0, ds = 0;
  for (int i = la - 1, j = lb - 1, k = ls - 1; k >= 0; --i, --j, --k) {
    da = i >= 0 ? (int) (a[i] - '0') : 0;
    db = j >= 0 ? (int) (b[j] - '0') : 0;
    ds = da + db + dc;
    dc = ds / 10;
    ds = ds % 10;
    s[k] = ds + '0';
  }
  
  int start = 0;
  string ret;
  while (s[start] == '0') {
     start++;
  }
  ret = string(&s[start], ls - start);
  delete s;
  return ret;
}

int main() {
  string line;
  string res ("0");
  while (getline(cin, line)) {
    if (line == "0") {
      break;  
    }
    res = sum(res, line);    
  }
  cout << res << endl;
  return 0;
}
