#include <algorithm>  // std::max
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace {
string RemovePaddingZeros(const string& s) {
  int i = 0;
  while (i < s.size() -1 && s[i] == '0') {
    i++;
  }
  return s.substr(i);
}

string AddStrings(const string& a, const string& b) {
  int za = a.size(), zb = b.size();
  string res(max(za, zb) + 1, '0');
  int carry = 0;
  for (int d = res.size() - 1; d >= 0; d--) {
    int i = za - res.size() + d;
    int j = zb - res.size() + d;
    if (0 <= i && i < za) {
      carry += (a[i] - '0');
    }
    if (0 <= j && j < zb) {
      carry += (b[j] - '0');
    }
    res[d] = (carry % 10) + '0';
    carry = carry / 10;
  }
  cout << "res: " << res << endl;
  return RemovePaddingZeros(res);
}

}  // namespace 

// NOTE: positive number only
//
// TODO: multiplication
// TODO: subtraction
// TODO: division
class BigInt {
 public:
  BigInt(const string& s) : str_(s) {}
  BigInt(const BigInt& o) : str_(o.str()) {}

  string str() const { return str_; }
  string& mutable_str() { return str_; }
  void set_str(const string& s) { str_ = s; }

  BigInt& operator =(const BigInt& other) {
    if (this != &other) {
      this->set_str(other.str());
    }
    return *this;
  }

  BigInt& operator=(BigInt&& other) noexcept { // move assignment
    if(this != &other) {
      swap(other.mutable_str(), str_);
    }
    return *this;
  }

  BigInt& operator += (const BigInt& rhs) {
    str_ = AddStrings(str_, rhs.str());
    return *this;
  }
  
  BigInt& operator += (const string& rhs) {
    str_ = AddStrings(str_, rhs);
    return *this;
  }

  //BigInt& operator ++() {
    //str_ = AddStrings(str_, "1");
    //return *this;
  //}

  friend BigInt operator + (BigInt lhs, const BigInt& rhs) {
    lhs += rhs;
    return lhs;
  }

  friend ostream& operator << (ostream &out, const BigInt& b) {
    out << b.str();
    return out; 
  }

 private:


  string str_;
};
 
inline bool operator< (const BigInt& lhs, const BigInt& rhs){
  if (lhs.str().size() < rhs.str().size()) {
    return true;
  }
  for (int i = 0; i < lhs.str().size(); ++i) {
    if (lhs.str()[i] < rhs.str()[i]) {
      return true;
    }
  }
  return false;
}
inline bool operator> (const BigInt& lhs, const BigInt& rhs){ return rhs < lhs; }
inline bool operator<=(const BigInt& lhs, const BigInt& rhs){ return !(lhs > rhs); }
inline bool operator>=(const BigInt& lhs, const BigInt& rhs){ return !(lhs < rhs); }
inline bool operator==(const BigInt& lhs, const BigInt& rhs){ return lhs.str() == rhs.str(); }
inline bool operator!=(const BigInt& lhs, const BigInt& rhs){ return !(lhs == rhs); }



// Test

int main() {
  BigInt a("22696209911206174");
  cout << a << endl;
  BigInt b("3658271912812123125");
  BigInt c = a + b;
  cout << c << endl;
  c += BigInt("1");
  c += "345";
  cout << c << endl;
}
