#include <algorithm>  // std::max
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

namespace {
string RemovePaddingZeros(const string& s) {
  int i = 0;
  // Keep last digit.
  while (i < s.size() -1 && s[i] == '0') {
    i++;
  }
  return s.substr(i);
}

// |a| and |b| are non-negative integers.
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
  return RemovePaddingZeros(res);
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
  if (carry < 0) cout << "[SubStrings] ERROR: Most significant carry < 0" << endl;
  return RemovePaddingZeros(res);
}

}  // namespace 

//
// Big unsigned integer.
//
// TODO: multiplication
// TODO: division
class BigUnsignedInt {
 public:
  BigUnsignedInt() {}
  BigUnsignedInt(const string& s) : str_(s) {
    if (s.empty()) cout << "[BigUnsignedInt] ERROR: empty string" << endl;
  }
  BigUnsignedInt(const char* c) : BigUnsignedInt(string(c)) {}
  BigUnsignedInt(const BigUnsignedInt& o) : BigUnsignedInt(o.str()) {}

  const string str() const { return str_; }
  string& mutable_str() { return str_; }
  void set_str(const string& s) { str_ = s; }

  BigUnsignedInt& operator=(const BigUnsignedInt& other) {
    if (this != &other) {
      this->set_str(other.str());
    }
    return *this;
  }

  BigUnsignedInt& operator=(BigUnsignedInt&& other) noexcept { // move assignment
    if(this != &other) {
      swap(other.mutable_str(), str_);
    }
    return *this;
  }

  BigUnsignedInt& operator += (const BigUnsignedInt& rhs) {
    str_ = AddStrings(str_, rhs.str());
    return *this;
  }
  
  // Ensure this >= rhs, otherwise the result is undefined.
  BigUnsignedInt& operator -= (const BigUnsignedInt& rhs) {
    str_ = SubStrings(str_, rhs.str());
    return *this;
  }

  friend BigUnsignedInt operator + (BigUnsignedInt lhs, const BigUnsignedInt& rhs) {
    lhs += rhs;
    return lhs;
  }

  friend BigUnsignedInt operator - (BigUnsignedInt lhs, const BigUnsignedInt& rhs) {
    lhs -= rhs;
    return lhs;
  }

  friend ostream& operator << (ostream &out, const BigUnsignedInt& b) {
    out << b.str();
    return out; 
  }

 private:
  string str_;
};
 
inline bool operator< (const BigUnsignedInt& lhs, const BigUnsignedInt& rhs){
  if (lhs.str().size() != rhs.str().size()) {
    return lhs.str().size() < rhs.str().size();
  }
  for (int i = 0; i < lhs.str().size(); ++i) {
    if (lhs.str()[i] -'0' < rhs.str()[i] - '0') {
      return true;
    }
  }
  return false;
}

inline bool operator> (const BigUnsignedInt& lhs, const BigUnsignedInt& rhs){ return rhs < lhs; }
inline bool operator<=(const BigUnsignedInt& lhs, const BigUnsignedInt& rhs){ return !(lhs > rhs); }
inline bool operator>=(const BigUnsignedInt& lhs, const BigUnsignedInt& rhs){ return !(lhs < rhs); }
inline bool operator==(const BigUnsignedInt& lhs, const BigUnsignedInt& rhs){ return lhs.str() == rhs.str(); }
inline bool operator!=(const BigUnsignedInt& lhs, const BigUnsignedInt& rhs){ return !(lhs == rhs); }


//
// Signed big integer.
//
// TODO: multiplication
// TODO: division
class BigInt {
 public:
  BigInt(const BigInt& o) : neg_(o.neg()), big_uint_(o.big_uint()) {}
  BigInt(const string& s) {
    if (s.empty()) cout << "[BigInt] ERROR: empty string" << endl;

    neg_ = s[0] == '-';
    if (neg_) {
      big_uint_ = s.substr(1);
    } else {
      big_uint_ = s;
    }
    CheckNegZero();
  }
  BigInt(const char* c) : BigInt(string(c)) {}

  BigInt(bool neg, const BigUnsignedInt& b) : neg_(neg), big_uint_(b) {}

  const BigUnsignedInt& big_uint() const { return big_uint_; }
  BigUnsignedInt& mutable_big_uint() { return big_uint_; }

  bool neg() const { return neg_; }
  void set_neg(bool neg) { neg_ = neg; }

  BigInt& operator=(const BigInt& other) {
    this->set_neg(other.neg());
    this->mutable_big_uint() = other.big_uint();
    return *this;
  }

  BigInt& operator=(BigInt&& other) noexcept { // move assignment
    if(this != &other) {
      swap(other.mutable_big_uint(), big_uint_);
      set_neg(other.neg());
    }
    return *this;
  }
  
  // Uniary '-'
  BigInt operator-() const {
    return BigInt(!neg_, big_uint_);
  }

  BigInt& operator += (const BigInt& rhs) {
    if (neg_ == rhs.neg()) {
      big_uint_ = big_uint_ + rhs.big_uint();
      return *this;
    }

    if (big_uint_ > rhs.big_uint()) {
      big_uint_ = big_uint_ - rhs.big_uint();
    } else {
      big_uint_ = rhs.big_uint() - big_uint_;
      neg_ = !neg_;
    }
    return *this;
  }
  
  BigInt& operator -= (const BigInt& rhs) {
    BigInt nrhs = -rhs;
    *this += nrhs;
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
    if (b.neg()) {
      out << "-";
    }
    out << b.big_uint();
    return out; 
  }

 private:
  // Not allow negative zero.
  void CheckNegZero() {
    if (big_uint_ == "0") neg_ = false;
  }

  bool neg_;
  BigUnsignedInt big_uint_;
};

inline bool operator< (const BigInt& lhs, const BigInt& rhs){
  if (lhs.neg() == rhs.neg()) {
    if (lhs.neg()) {  // Both negative
      return lhs.big_uint() > rhs.big_uint();
    } else {
      return lhs.big_uint() < rhs.big_uint();
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
         lhs.big_uint() == rhs.big_uint();
}
inline bool operator!=(const BigInt& lhs, const BigInt& rhs){ return !(lhs == rhs); }

bool Solve(const string& line) {
  BigUnsignedInt num(line);

  while (num.str().size() >= 4) {
    string s = num.str();
    BigUnsignedInt x = s.substr(0, s.size()-1);
    BigUnsignedInt y = to_string((s[s.size()-1] - '0')*5);
    num = x - y;
  }

  // stoi(s) < 1000
  string s = num.str();
  int i = stoi(s);
  return i % 17 == 0;
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line == "0") break;
    cout << (Solve(line) ? 1 : 0) << endl;
  }
}
