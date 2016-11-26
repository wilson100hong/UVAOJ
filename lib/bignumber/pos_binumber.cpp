// positive big number arithmetic:
// 1. add
// 2. subtract
// 3. multiply
// 4. divide
// 5. gcd
// 6. compare

// TODO: support negative bignumber


#include <iostream>
#include <utility>
#include <tuple>
using namespace std;

int max(int a, int b) {
  return a > b ? a : b;
}

// remove leading 0
string lstrip_zeros(const string& s) {
  int cur = 0;
  while (s[cur] == '0' && cur < s.size()) {
    cur++;
  }
  if (cur == s.size()) {
    return "0";
  }
  return s.substr(cur);
}

// return:
// -1 if s1 < s2
// 0 if s1 == s2
// 1 if s1 > s2
int bigcomp(const string& s1, const string& s2) {
  if (s1.size() != s2.size()) {
    return s1.size() < s2.size() ? -1 : 1;
  }
  for (int i=0;i<s1.size();++i) {
    if (s1[i] != s2[i]) {
      return s1[i] < s2[i] ? -1 : 1;
    }
  }
  return 0;
}

string bigadd(const string& s1, const string& s2) {
  int n1 = s1.size(), n2 = s2.size();
  int n = max(n1, n2) + 1;
  string res(n, '0');
  int carry = 0;
  for (int i=0;i<n;++i) {
    int d1 = n1-1-i >= 0 ? s1[n1-1-i]-'0' : 0;
    int d2 = n2-1-i >= 0 ? s2[n2-1-i]-'0' : 0;
    int dr = d1 + d2 + carry;
    res[res.size()-1-i] = (dr%10) + '0';
    carry = dr / 10;
  }
  return lstrip_zeros(res);
}

// return s1 - s2, s1 >= s2
string bigsub(const string& s1, const string& s2) {
  int n1 = s1.size(), n2 = s2.size();
  string res(n1, '0');
  int carry = 0;
  for (int i=0;i<n1;++i) {
    int d1 = s1[n1-1-i]-'0';
    int d2 = n2-1-i >= 0 ? s2[n2-1-i]-'0' : 0;
    d2 += carry;
    carry = 0;
    if (d1 < d2) {
      carry = 1;
      d1 += 10;
    }
    int dr = (d1-d2) % 10;
    res[n1-1-i] = dr + '0';
  }
  return lstrip_zeros(res);
}

// return s1*s2
string bigmul(const string& s1, const string& s2) {
  int n1 = s1.size(), n2 = s2.size();
  int n = n1+n2;
  string res(n1+n2, '0');
  for (int i=0;i<n2;++i) {
    int d2 = s2[n2-1-i]-'0';
    int carry = 0;
    for (int j=0;j<n1;++j) {
      int d1 = s1[n1-1-j]-'0';
      int dr = (res[n-1-(i+j)]-'0') + d1*d2 + carry;
      res[n-1-(i+j)] = (dr%10) + '0';
      carry = dr/10;
    }
    int cur = i+n1;
    while (carry > 0) {
      int dr = res[n-1-cur]-'0' + carry;
      carry = dr/10;
      res[n-1-cur] = (dr%10) + '0';
      cur++;
    }
  }
  return lstrip_zeros(res);
}

// return s/2
string bighalf(const string& s) {
  string res(s.size(), '0');
  int carry = 0;
  for (int i=0;i<s.size();++i) {
    int d = (s[i]-'0') + carry;
    res[i] = (d/2) + '0';
    carry = (d%2)*10;
  }
  return lstrip_zeros(res);
}

// return <quotient, remainder> for s1/s2
pair<string, string> bigdiv(const string& s1, const string& s2) {
  if (s2 == "0") {
    cout << "DIV BY ZERO" << endl;
    exit(1);
  }
  string q = "0", r = s1;

  // binary search
  string lb = "1", rb = s1;
  while (bigcomp(lb, rb) <= 0) {  // lb <= rb
    string med = bighalf(bigadd(lb, rb));  // (lb+rb)/2
    string mul = bigmul(s2, med);
    int comp = bigcomp(s1, mul);
    if (comp < 0) {
      // s1 < s2*med
      rb = bigsub(med, "1");
    } else {
      q = med;
      r = bigsub(s1, mul);
      if (comp == 0) {
        break;
      } else {
        // s1 > s2*med
        lb = bigadd(med, "1");
      }
    }
  }
  return {q, r};
}

string gcd(const string& s1, const string& s2) {
  if (bigcomp(s1, s2) < 0) {
    return gcd(s2, s1);
  }
  if (s2 == "0") {
    return s1;
  }

  string quotient, remainder;
  tie(quotient, remainder) = bigdiv(s1, s2);
  if (remainder == "0") {
    return s2;
  }
  return gcd(s2, remainder);
}

