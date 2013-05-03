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

int numdigit(int a) {
    int n = 1;
    while (a / 10 > 0) {
      n++;
      a /= 10;
    }
    return n;
}

string scinum(int frac, int exp) {
    int d = numdigit(frac);
    string s(d + exp, '0');
    for (int i = d - 1; i >= 0; --i) {
        s[i] = (char) (frac % 10 + '0');
        frac /= 10;
    }
    return s;
}

/**
 Add an integer to big numbers.
 input:
 frac : the fraction part, must < 10000
 exp  : the exponential part, which is power of 10.
 */
string bigsum(string s, int frac, int exp) {
    return bigsum(s, scinum(frac, exp));
}

/**
 retrieve part from s with exp offset. Only x digit part will be return
 eg. part("12345", 0) = 2345
 part("12345", 1) = 1234
 part("234", 0) = 234
 part("123, 2) = 1
 part("99998888", 8) = 0;
 */
int part(string s, int exp, int x) {
    int len = s.length();
    if (exp >= len)
        return 0;
    // len must > exp
    int start = len - exp - x;
    if (start < 0) {
        x += start;
        start = 0;
    }
    int sum = 0;
    while (start < len && x > 0) {
        sum *= 10;
        sum += (int) (s[start] - '0');
        x--;
        start++;
    }
    return sum;
}

/*
 Calculate a * b
 We use multiplication learned from elementary school
 a =   a2 a1 a0
 b = x    b1 b0
 -------------------
 ma0b0  (a0 x b0)
 ma1b0     (a1 x b0)
 ma2b0        (a2 x b0)
 ma0b1     (a0 x b1)
 ma1b1        (a1 x b1)
 +  ma2b1          (a2 x b1)
 ---------------------
 
 For each round, calculate one chunk (ai x bj), coumpute the multiplication maibj,
 combine maibj with the power of 10 offset to form a new string, then use bigsum
 to sum them together get a new string.
 */
string bigmul(string a, string b) {
    string sum = "0";
    int j = 0;
    int lb = b.length();
    // TODO(wilsonhong): bug
    while (lb > 0) {
        int bj = part(b, 4 * j, 4);
        int i = 0;
        int la = a.length();
        // TODO(wilsonhong): bug
        while (la > 0) {
            int ai = part(a, 4 * i, 4);
            int mij = ai * bj;
            string tij = scinum(mij, 4 * (i + j));
            sum = bigsum(sum, tij);
            i++;
            la -= 4;
        }
        j++;
        lb -= 4;
    }
    return sum;
}

string itoa(int n) {
  return scinum(n, 0); 
}

string factorial(int n) {
  string x = "1";
  for (int i = 2; i <= n; ++i) {
    x = bigmul(x, itoa(i));
  }
  return x;
}

int main() {
  int n;
  int cnt[10];
  while (cin >> n) {
    if (n == 0)
      break;
    for (int i = 0; i < 10; ++i)
      cnt[i] = 0;
    string x = factorial(n);
    int len = x.length();
    for (int i = 0; i < len; ++i) {
      int index = (int) (x[i] - '0');
      cnt[index]++;
    }
    cout << n << "! --";
    for (int i = 0; i < 10; ++i) {
      if (i % 5 == 0) 
        cout << endl;
      else 
        cout << " ";
      cout << "   (" << i << ")";
      cout.setf(ios::right);
      cout.width(5);
      cout << cnt[i];
    }
    cout << endl;
 }
 
  return 0;
}
