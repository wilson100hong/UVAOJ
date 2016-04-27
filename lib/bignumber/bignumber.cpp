// Bignumber arithematics.
// Currently it support addition, subtraction and multiplication
// All string digits starting from largest digit.
// string "12345" means 12345
//
// TODO: try to avoid do comparison in bigsub_pos
//
#include <iostream>
#include <vector>
using namespace std;

bool is_negative(string s) {
  return s[0] == '-';
}

string bigabs(string s) {
  return is_negative(s) ? s.substr(1) : s;
}

string flip_sign(string s) {
  if (is_negative(s)) {
    return s.substr(1);
  } else {
    return "-" + s;
  }
}

string strip_leading_zeros(string s) {
  int start = 0;
  while (s[start] == '0' && start < s.size() - 1) {
    start++;
  }
  return s.substr(start);
}

// addition for positive number s1 and s2
string bigadd_pos(string s1, string s2) {
  int size = max(s1.size(), s2.size()) + 1;
  string result(size, '0');
  int carry = 0; 
  for (int k = size - 1, i = s1.size() - 1, j = s2.size() - 1; k >= 0; --k, --i, --j) {
    int di = i >= 0 ? s1[i] - '0' : 0;
    int dj = j >= 0 ? s2[j] - '0' : 0;
    int dk = carry + di + dj;
    carry = dk / 10;
    result[k] = (dk % 10) + '0';
  }
  return strip_leading_zeros(result);
}

// compare two positive number s1 and s2. Return true if s1 > s2
bool larger_pos(string s1, string s2) {
  int len1 = s1.size(), len2 = s2.size();
  if (len1 != len2) return len1 > len2;
  // both numbers have the same length
  for (int i = 0; i < s1.size(); ++i) {
    if (s1[i] == s2[i]) continue;
    return s1[i] > s2[i];
  }
  return false;  // s1 == s2
}

// subtraction for positive numbers s1 and s2. It is possible that s1 < s2
string bigsub_pos(string s1, string s2) {
  if (larger_pos(s2, s1)) {
    return flip_sign(bigsub_pos(s2, s1));
  }
 
  int size = max(s1.size(), s2.size());
  string result(size, '0');
  int carry = 0; 
  for (int k = size - 1, i = s1.size() - 1, j = s2.size() - 1; k >= 0; --k, --i, --j) {
    int di = i >= 0 ? s1[i] - '0' : 0;
    int dj = j >= 0 ? s2[j] - '0' : 0;
    di += carry;
    carry = 0;
    if (di < dj) {
      di += 10;
      carry = -1;  // borrow the bit
    }
    int dk = di - dj;
    carry += (dk / 10);  // this should be no-op
    result[k] = (dk % 10) + '0';
  }
  return strip_leading_zeros(result);
}

// multiplication for positive numbers s1 and s2
string bigmul_pos(string s1, string s2) {
  int size = s1.size() + s2.size();
  vector<int> buffer(size, 0);
  for (int i = s1.size() - 1; i >= 0; --i) {
    int di = s1[i] - '0', carry = 0;
    for (int j = s2.size() - 1; j >= 0; --j) {
      int dj = s2[j] - '0';
      int offset = s1.size() - 1 - i + s2.size() - 1 - j;
      int sum = di * dj + carry + (buffer[offset]);
      buffer[offset] = sum % 10;
      carry = sum / 10;
    }
    // handle carry
    int start = s2.size() + s1.size() - 1 - i, index = 0;
    while (carry > 0) {
      int sum = buffer[start + index] + carry;
      buffer[start + index] = sum % 10;
      carry = sum / 10;
      index++;
    }
  }
  // generate result
  string result(size, '0');
  for (int i = 0; i < size; ++i) {
    result[size - i - 1] = buffer[i] + '0';
  }
  return strip_leading_zeros(result);
}

string bigadd(string s1, string s2) {
  bool n1 = is_negative(s1), n2 = is_negative(s2);
  if (n1 ^ n2) {
    // one is positive, negative
    if (n1) {
      return bigsub_pos(s2, bigabs(s1));
    } else {  // s2 < 0 
      return bigsub_pos(s1, bigabs(s2));
    }
  } if (n1 && n2) {
    // both are negative
    return flip_sign(bigadd_pos(bigabs(s1), bigabs(s2)));  // make it negative
  } else {
    // both are positive
    return bigadd_pos(s1, s2);
  }
}

string bigsub(string s1, string s2) {
  return bigadd(s1, flip_sign(s2));
}

string bigmul(string s1, string s2) {
  bool n1 = is_negative(s1), n2 = is_negative(s2);
  string tmp = bigmul_pos(bigabs(s1), bigabs(s2));
  return (n1 ^ n2) ? flip_sign(tmp) : tmp;
}


int main() {
  cout << bigadd("0", "0") << endl;
  cout << bigadd("123456789123456789", "7654321987654321") << endl;
  cout << bigadd("-123456789123456789", "7654321987654321") << endl;
  cout << bigadd("123456789123456789", "-7654321987654321") << endl;
  cout << bigadd("-123456789123456789", "-7654321987654321") << endl;

  cout << bigsub("123456789012345", "123456789012345") << endl;
  cout << bigsub("123456789123456789", "7654321987654321") << endl;
  cout << bigsub("-123456789123456789", "7654321987654321") << endl;
  cout << bigsub("123456789123456789", "-7654321987654321") << endl;
  cout << bigsub("-123456789123456789", "-7654321987654321") << endl;
  cout << bigsub("123456789012345", "0") << endl;
  cout << bigsub("0", "123456789012345") << endl;

  cout << bigmul ("0", "123456789012345") << endl;
  cout << bigmul ("0", "0") << endl;
  cout << bigmul("123456789123456789", "7654321987654321") << endl;
  cout << bigmul("-123456789123456789", "7654321987654321") << endl;
  cout << bigmul("123456789123456789", "-7654321987654321") << endl;
  cout << bigmul("-123456789123456789", "-7654321987654321") << endl;
}
