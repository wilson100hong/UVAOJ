#include <algorithm>  // std::max
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>

using namespace std;

namespace {
string RemoveLeadingZeros(const string& s) {
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
  return RemoveLeadingZeros(res);
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
  if (carry < 0) cout << "[SubStrings] ERROR: Most significant carry < 0" <<
    endl; return RemoveLeadingZeros(res);
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
  BigUnsignedInt(const string& s) : str_(RemoveLeadingZeros(s)) {
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
    const char lc = lhs.str()[i], rc = rhs.str()[i];
    if (lc == rc) continue;
    return lc < rc;
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

  const string GetStr() const {
    string res = neg_ ? "-" : ""; return res + big_uint_.str();
  }

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
    CheckNegZero();
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
    out << b.GetStr();
    return out; 
  }

 private:
  // Do not allow "-0".
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

////////////////////////

// Return BigInt, decimal offset.
struct BigFloat {
  BigInt big_int;  // Allow trailing zeros.
  int offset;  // decimal offset
};

BigFloat StrToBigFloat(const string& str) {
  size_t cur = 0;
  while (cur < str.size()) {
    if (str[cur] == '.') break;
    cur++;
  }
  if (cur >= str.size()) {
    return {BigInt(str), 0};
  }
  return {BigInt(str.substr(0, cur) + str.substr(cur+1)), static_cast<int>(str.size()-1-cur)};
}

string BigFloatToStr(const BigFloat& big_float) {
  string ubs = big_float.big_int.big_uint().str();
  string res;
  if (big_float.big_int.big_uint() == "0") {
    return "0";
  } else if (big_float.offset >= ubs.size()) {
    res = "0." + string(big_float.offset - ubs.size(), '0') + ubs;
  } else {  // offset < ubs.size()
    const size_t m_size = ubs.size() - big_float.offset;
    res = ubs.substr(0, m_size);
    if (m_size < ubs.size()) {
      res = res + "." + ubs.substr(m_size);
    }
  }

  if (big_float.big_int.neg()) {
    res = "-" + res;
  }
  return res;
}

void LeftOffset(BigFloat* big_float, int offset) {
  string ns = big_float->big_int.GetStr() + string(offset, '0');
  big_float->big_int = ns;
  big_float->offset += offset;
}

// Adjusts offset to remove decimal part trailing zeros.
void RemoveTrailingZeros(BigFloat* big_float) {
  string bs = big_float->big_int.GetStr();
  while (big_float->offset > 0 &&
         bs.size() > 1 &&
         bs.back() == '0') {
    big_float->offset--;
    bs.pop_back();
  }

  big_float->big_int = BigInt(bs);
}

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  int N;
  ss >> N;
  while (N--) {
    BigFloat res{BigInt("0"), 0};
    while (1) {
      getline(cin, line);
      if (line == "0") break;
      //cout << line << endl;

      BigFloat given = StrToBigFloat(line);

      if (res.offset > given.offset) {
        LeftOffset(&given, res.offset - given.offset);
      } else if (res.offset < given.offset) {
        LeftOffset(&res, given.offset - res.offset);
      }

      res = {res.big_int + given.big_int, res.offset};
      RemoveTrailingZeros(&res);
    }
    RemoveTrailingZeros(&res);
    cout << BigFloatToStr(res) << endl;
  }
}
  
