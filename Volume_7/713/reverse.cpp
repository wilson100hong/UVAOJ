#include <iostream>
using namespace std;
string bigsum(string a, string b) {
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
    while (s[start] == '0' && start < ls - 1)
        start++;
    string ret = string(&s[start], ls - start);
    delete s;
    return ret;
}

string remove_leading_zero(string& s) {
  int start = 0;
  while (s[start] == '0' && start < s.length() - 1)
    start++;
  string ret = string(&s[start], s.length() - start);
  return ret;
}

string reverse(string& s) {
  int start = 0, end = s.length() - 1;
  while (start < end) {
    char tmp = s[start];
    s[start] = s[end];
    s[end] = tmp;
    start++;
    end--;
  }
  return remove_leading_zero(s);
}

int main () {
  int n;
  cin >> n;
  while (n-- > 0) {
    string a, b;
    cin >> a >> b;
    a = remove_leading_zero(a);
    b = remove_leading_zero(b);
    string rsum = bigsum(reverse(a), reverse(b));
    cout << reverse(rsum) << endl;
  }
  return 0;
}
