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
    string ret;
    while (s[start] == '0') {
        start++;
    }
    ret = string(&s[start], ls - start);
    delete s;
    return ret;
}

int main() {
  string fib[5001];
  fib[0] = "0";
  fib[1] = "1";
  fib[2] = "1";
  for (int i = 3; i < 5001; ++i) 
    fib[i] = bigsum(fib[i-1], fib[i-2]);
  int n;
  while (cin >> n)
    cout << "The Fibonacci number for " << n << " is " << fib[n] << endl;

}
