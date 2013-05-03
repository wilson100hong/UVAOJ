#include <iostream>
#include <string>
#include <sstream>

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
  string s;
  stringstream ss(s);
  ss << n;
  return ss.str();
}


string mul(int a, int b) {
  return bigmul(itoa(a), itoa(b));
}

int main() {
  int cut;
  while (cin >> cut) {
    if (cut < 0) {
      break;  
    }
    int cutmore = cut + 1;
    if (cut % 2 == 0) {
      cut = cut / 2;
    } else {
      cutmore = cutmore / 2;  
    }
    string m = mul(cut, cutmore);
    cout << bigsum(m, "1") << endl;
  }
  return 0;
}
