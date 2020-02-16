#include <algorithm>  // std::max
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////
namespace {
string StripLZeros(const string& s) {
  int i = 0;
  while (i < s.size()-1 && s[i] == '0') {
    i++;
  }
  return s.substr(i);
}

// |a| and |b| are unsigned integer strings.
bool LessStrings(const string& a, const string& b) {
  if (a.size() != b.size()) {
    return a.size() < b.size();
  }

  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) {
      return a[i] < b[i];
    }
  }
  return false;
}

// |a| and |b| are unsigned integer strings.
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

// |a| and |b| are unsigned integer strings.
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

// |a| and |b| are unisgned integer strings.
string MulStrings(const string& a, const string& b) {
  string res(a.size() + b.size(), '0');
  for (int i=a.size()-1;i>=0;--i) {
    for (int j=b.size()-1;j>=0;--j) {
      int offset = res.size()-1 - (a.size()-1-i + b.size()-1-j);
      int m = (a[i]-'0')*(b[j]-'0') + (res[offset]-'0');
      res[offset] = (m % 10) + '0';
      int carry = m / 10;
      while (carry) {
        offset--;
        int a = res[offset]-'0' + carry;
        res[offset] = (a % 10) + '0';
        carry = a / 10;
      }
    }
  }
  return StripLZeros(res);
}

// Returns quotient of a//b
// |a| and |b| are unsigned integer strings.
string DivStrings(const string& a, const string& b) {
  if (LessStrings(a, b)) {
    return "0";
  }
  // |a| >= |b|
  string q;
  int offset = b.size() - 1;
  string c = a.substr(0, b.size());
  while (offset < a.size()) {
    int d = 0;
    while (!LessStrings(c, b)) {
      c = SubStrings(c, b);
      d++;
    }
    q += to_string(d);
    offset++;
    if (offset < a.size()) {
      c = StripLZeros(c + a[offset]); // case 00..0
    }
  }
  return StripLZeros(q);
}

}  // namespace 

//
// Unsigned big integer.
//
class UnsignedBigInt {
 public:
  UnsignedBigInt() {}
  UnsignedBigInt(const string& s) : str_(StripLZeros(s)) {
    if (s.empty()) {
      cout << "[UnsignedBigInt] ERROR: empty string" << endl;
    }
  }
  UnsignedBigInt(unsigned long long ll) : str_(to_string(ll)) {}
  UnsignedBigInt(const UnsignedBigInt& o) : UnsignedBigInt(o.str()) {}

  const string str() const { return str_; }
  string& mutable_str() { return str_; }
  void set_str(const string& s) { str_ = s; }

  UnsignedBigInt& operator=(const UnsignedBigInt& other) {
    if (this != &other) {
      set_str(other.str());
    }
    return *this;
  }
  
  UnsignedBigInt& operator=(unsigned long long ll) {
    set_str(to_string(ll));
    return *this;
  }

  UnsignedBigInt& operator=(UnsignedBigInt&& other) noexcept {
    if(this != &other) {
      swap(other.mutable_str(), str_);
    }
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

  UnsignedBigInt& operator *= (const UnsignedBigInt& rhs) {
    str_ = MulStrings(str_, rhs.str());
    return *this;
  }
  
  UnsignedBigInt& operator /= (const UnsignedBigInt& rhs) {
    str_ = DivStrings(str_, rhs.str());
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

  friend UnsignedBigInt operator * (UnsignedBigInt lhs, const UnsignedBigInt& rhs) {
    lhs *= rhs;
    return lhs;
  }

  friend UnsignedBigInt operator / (UnsignedBigInt lhs, const UnsignedBigInt& rhs) {
    lhs /= rhs;
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
  return LessStrings(lhs.str(), rhs.str());
}

inline bool operator> (const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return rhs < lhs; }
inline bool operator<=(const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return !(lhs > rhs); }
inline bool operator>=(const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return !(lhs < rhs); }
inline bool operator==(const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return lhs.str() == rhs.str(); }
inline bool operator!=(const UnsignedBigInt& lhs, const UnsignedBigInt& rhs){ return !(lhs == rhs); }


///////////////////////////////////////////////////////////////////////////////////////////////

void Solve(const string& input, const vector<string>& factors) {
  bool wonderful = true;
  UnsignedBigInt nom(input);
  for (const string& factor : factors) {
    UnsignedBigInt denom(factor);
    auto q = nom / denom;
    if (nom != q * denom) {
      wonderful = false;
      break;
    }
  }

  cout << input << " - ";
  if (wonderful) {
    cout << "Wonderful." << endl;
  } else {
    cout << "Simple." << endl;
  }
}


int main() {
  string line;
  int TC;
  cin >> TC;
  getline(cin, line);
  while (TC--) {
    string input, dummy;
    cin >> input;
    getline(cin, dummy);

    getline(cin, line);
    stringstream ss(line);
    string n_f;
    ss >> n_f;
    vector<string> factors;
    string factor;
    while (ss >> factor) {
      factors.push_back(factor);
    }
    Solve(input, factors);
  }
}
