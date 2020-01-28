#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
//////// Big Number ////////

namespace {
string StripLZeros(const string& s) {
  int i = 0;
  while (i < s.size()-1 && s[i] == '0') {
    i++;
  }
  return s.substr(i);
}

// |a| and |b| are strings for unsigned integers.
string AddStrings(const string& a, const string& b) {
  string res(max(a.size(), b.size()) + 1, '0');
  int carry = 0;
  for (int d = res.size()-1; d >= 0; d--) {
    const int i = a.size() - res.size() + d;  // cursor of |a|
    const int j = b.size() - res.size() + d;  // cursor of |b|
    if (0 <= i && i < a.size()) {
      carry += (a[i] - '0');
    }
    if (0 <= j && j < b.size()) {
      carry += (b[j] - '0');
    }
    res[d] = (carry % 10) + '0';
    carry = carry / 10;
  }
  return StripLZeros(res);
}

// |a| >= |b|. Otherwise the result is undefined.
string SubStrings(const string& a, const string& b) {
  string res(a);
  int carry = 0;
  for (int i = res.size()-1; i >=0; i--) {
    carry += (res[i] - '0');
    const int j = b.size() - res.size() + i;  // cursor of |b|
    if (0 <= j && j < b.size()) {
      carry -= (b[j] - '0');
    }
    res[i] = (carry + 10) % 10 + '0';
    carry = carry < 0 ? -1 : 0; 
  }

  // carry should be zero here.
  if (carry < 0) {
    cout << "[SubStrings] ERROR: Most significant carry < 0" << endl;
  }
  return StripLZeros(res);
}

}  // namespace 

//
// Unsigned big integer.
//
// TODO: multiplication
// TODO: division
class UnsignedBigInt {
 public:
  UnsignedBigInt() {}
  UnsignedBigInt(const string& s) : str_(StripLZeros(s)) {
    if (s.empty()) {
      cout << "[UnsignedBigInt] ERROR: empty string" << endl;
    }
  }
  UnsignedBigInt(unsigned long long ll) : str_(to_string(ll)) {}
  UnsignedBigInt(const char* c) : UnsignedBigInt(string(c)) {}
  UnsignedBigInt(const UnsignedBigInt& o) : UnsignedBigInt(o.str()) {}

  const string str() const { return str_; }
  //string& mutable_str() { return str_; }
  void set_str(const string& s) { str_ = s; }

  UnsignedBigInt& operator=(const UnsignedBigInt& other) {
    if (this != &other) {
      str_ = other.str();
    }
    return *this;
  }

  UnsignedBigInt& operator=(unsigned long long ll) {
    str_ = to_string(ll);
    return *this;
  }

  UnsignedBigInt& operator += (const UnsignedBigInt& rhs) {
    str_ = AddStrings(str_, rhs.str());
    return *this;
  }
  
  // Ensure this >= rhs, otherwise the result is undefined.
  UnsignedBigInt& operator -= (const UnsignedBigInt& rhs) {
    str_ = SubStrings(str_, rhs.str());
    return *this;
  }

  friend UnsignedBigInt operator + (UnsignedBigInt lhs, const UnsignedBigInt& rhs) {
    lhs += rhs;
    return lhs;
  }

  friend UnsignedBigInt operator - (UnsignedBigInt lhs, const UnsignedBigInt& rhs) {
    lhs -= rhs;
    return lhs;
  }


  friend ostream& operator << (ostream &out, const UnsignedBigInt& b) {
    out << b.str();
    return out; 
  }

 private:
  string str_;
};
 
inline bool operator< (const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){
  if (lhs.str().size() != rhs.str().size()) {
    return lhs.str().size() < rhs.str().size();
  }
  for (int i = 0; i < lhs.str().size(); ++i) {
    const char lc = lhs.str()[i], rc = rhs.str()[i];
    if (lc == rc) continue;
    return lc < rc;
  }
  return false;
}

inline bool operator> (const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return rhs < lhs; }
inline bool operator<=(const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return !(lhs > rhs); }
inline bool operator>=(const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return !(lhs < rhs); }
inline bool operator==(const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return lhs.str() == rhs.str(); }
inline bool operator!=(const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return !(lhs == rhs); }

//////// BIG NUMBER ////////

#define MAX_N 51

UnsignedBigInt CNR[MAX_N][MAX_N];

void Init() {
  for (int i=0;i<MAX_N;++i) {
    for (int j=0;j<MAX_N;++j) {
      CNR[i][j] = 0;
    }
  }
  for (int i=0;i<MAX_N;++i) {
    CNR[i][i] = 1;
    CNR[i][0] = 1;
  }

  for (int i=1;i<MAX_N;++i) {
    for (int j=1;j<i;++j) {
      CNR[i][j] = CNR[i-1][j-1] + CNR[i-1][j];
    }
  }
}

// a^r*b^(n-r)
string ToToken(const string& a, const string& b, int n, int r) {
  UnsignedBigInt coeff = CNR[n][r];
  string res = coeff == "1" ? "" : coeff.str() + "*";
  if (r > 0) {
    res += a;
    if (r > 1) res += "^" + to_string(r);
  }
  if (n-r > 0) {
    if (r!=0) res += "*";
    res += b;
    if (n-r > 1) res += "^" + to_string(n-r);
  }
  return res;
}

string Solve(string str) {
  // str[0] == '('
  str = str.substr(1);
  int cur = 0;
  while (cur < str.size() && str[cur] != '+') {
    cur++;
  }
  string a = str.substr(0, cur);
  str = str.substr(cur+1); 
  cur = 0;

  while (cur < str.size() && str[cur] != ')') {
    cur++;
  }
  string b = str.substr(0, cur);
  str = str.substr(cur+2);  // skip ")^"

  int n = stoi(str);
  string res;
  bool first = true;
  for (int r=n;r>=0;--r) {
    if (!first) res += "+";
    res += ToToken(a, b, n, r);
    first = false;
  }
  return res;
}

int main() {
  Init();
  string line;
  getline(cin, line);
  stringstream ss(line);
  int cases;
  ss >> cases;
  for (int case_num = 1; case_num <= cases; ++case_num) {
    getline(cin, line);
    cout << "Case " << case_num << ": " << Solve(line) << endl;
  } 
}
