#include <algorithm>  // std::max
#include <iostream>
#include <vector>
#include <string>

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
//
// Signed big integer.
//
// TODO: multiplication
// TODO: division
class BigInt {
 public:
  BigInt() {}
  BigInt(const BigInt& o) : neg_(o.neg()), ubigint_(o.ubigint()) {}

  BigInt(const string& s) {
    if (s.empty()) {
      cout << "[BigInt] ERROR: empty string" << endl;
    }
    neg_ = s[0] == '-';
    ubigint_ = neg_ ? s.substr(1) : s;

    CheckNegZero();
  }

  //BigInt(const char* c) : BigInt(string(c)) {}

  BigInt(bool neg, const UnsignedBigInt& b) : neg_(neg), ubigint_(b) {}

  const UnsignedBigInt& ubigint() const { return ubigint_; }
  UnsignedBigInt& mutable_ubigint() { return ubigint_; }

  string ToStr() const {
    string res = ubigint_.str();
    if (neg_) {
      res = "-" + res;
    }
    return res;
  }

  bool neg() const { return neg_; }
  void set_neg(bool neg) { neg_ = neg; }

  BigInt& operator=(const BigInt& other) {
    this->set_neg(other.neg());
    this->mutable_ubigint() = other.ubigint();
    return *this;
  }

  BigInt& operator=(BigInt&& other) noexcept { // move assignment
    if(this != &other) {
      swap(other.mutable_ubigint(), ubigint_);
      set_neg(other.neg());
    }
    return *this;
  }
  
  // Uniary '-'
  BigInt operator-() const {
    return BigInt(!neg_, ubigint_);
  }

  BigInt& operator += (const BigInt& rhs) {
    if (neg_ == rhs.neg()) {
      ubigint_ = ubigint_ + rhs.ubigint();
      return *this;
    }

    if (ubigint_ > rhs.ubigint()) {
      ubigint_ = ubigint_ - rhs.ubigint();
    } else {
      ubigint_ = rhs.ubigint() - ubigint_;
      neg_ = !neg_;
    }
    CheckNegZero();
    return *this;
  }
  
  BigInt& operator -= (const BigInt& rhs) {
    *this += (-rhs);
    return *this;
  }

  friend BigInt operator + (BigInt lhs, const BigInt& rhs) {
    lhs += rhs;
    return lhs;
  }

  friend BigInt operator - (BigInt lhs, const BigInt& rhs) {
    lhs -= rhs;
    return lhs;
  }

  friend ostream& operator << (ostream &out, const BigInt& b) {
    out << b.ToStr();
    return out; 
  }

 private:
  // Do not allow -0.
  void CheckNegZero() {
    if (ubigint_.str() == "0") {
      neg_ = false;
    }
  }

  bool neg_;
  UnsignedBigInt ubigint_;
};

inline bool operator< (const BigInt& lhs, const BigInt& rhs){
  if (lhs.neg() == rhs.neg()) {
    if (lhs.neg()) {  // Both negative
      return lhs.ubigint() > rhs.ubigint();
    } else {
      return lhs.ubigint() < rhs.ubigint();
    }
  } else {
    return lhs.neg();
  }
}

inline bool operator> (const BigInt& lhs, const BigInt& rhs){ return rhs < lhs; }
inline bool operator<=(const BigInt& lhs, const BigInt& rhs){ return !(lhs > rhs); }
inline bool operator>=(const BigInt& lhs, const BigInt& rhs){ return !(lhs < rhs); }
inline bool operator==(const BigInt& lhs, const BigInt& rhs){
  return lhs.neg() == rhs.neg() &&
         lhs.ubigint() == rhs.ubigint();
}
inline bool operator!=(const BigInt& lhs, const BigInt& rhs){ return !(lhs == rhs); }


///////////////////////////////////////////////////////////////////////////////////////////////
//
// Big floating number
//
class BigFloat {
 public:
  BigFloat() {}
  
  BigFloat(const string& s) {
    size_t cur = 0;
    while (cur < s.size()) {
      if (s[cur] == '.') break;
      cur++;
    }
    if (cur >= s.size()) {
      bigint_ = s;
      offset_ = 0;
    } else {
      bigint_ = s.substr(0, cur) + s.substr(cur+1);
      offset_ = s.size() - 1 - cur;
    }
  }

  string ToStr() const {
    string ubs = bigint_.ubigint().str();
    if (ubs == "0") {
      return "0";
    }
    
    string res;
    if (ubs.size() <= offset_) {
      res = "0." + string(offset_ - ubs.size(), '0') + ubs;
    } else {  // offset < ubs.size()
      const size_t m_size = ubs.size() - offset_;
      res = ubs.substr(0, m_size);
      if (m_size < ubs.size()) {
        res = res + "." + ubs.substr(m_size);
      }
    }

    return (bigint_.neg() ? "-" : "") + res;
  }

 private:
  void LeftOffset(int offset) {
    bigint_ = bigint_.ToStr() + string(offset, '0');
    offset_ += offset;
  }


  //  remove decimal part trailing zeros.
  void UpdateOffset() {
    string bs = bigint_.ToStr();
    while (offset_ > 0 &&
        bs.size() > 1 &&
        bs.back() == '0') {
      offset_--;
      bs.pop_back();
    }

    bigint_ = bs;
    //big_float->big_int = BigInt(bs);
  }

  BigInt bigint_;
  int offset_;  // decimal offset
};


///////////////////////////////////////////////////////////////////////////////////////////////
//
// Test
//
int main() {
  UnsignedBigInt a = string("987654321");
  UnsignedBigInt b = string("12345");
  cout << a / b << endl;
  //cout << a * b * 4 << endl;
  //BigInt a("22696209911206174");
  //BigInt b("3658271912812123125");
  //cout << a - b << endl;
  
  //BigInt a("345");
  //BigInt b("98");
  //cout << a + b << endl;

  //BigInt a("0");
  //BigInt b("123");
  //cout << a - b << endl;
  //cout << "a == b ? " << (a == b) << endl;
  //cout << "a < b ? " << (a < b) << endl;
  //cout << "a > b ? " << (a > b) << endl;

  //b = a;
  //cout << "a == b ? " << (a == b) << endl;
  //cout << "a < b ? " << (a < b) << endl;
  //cout << "a > b ? " << (a > b) << endl;
}
