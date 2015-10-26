#include <iostream>
#include <vector>
using namespace std;

/************ BIGNUMBER ************/
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
/************ BIGNUMBER ************/

#define MAX_SIZE 60

int main() {
  vector<string>* vec = new vector<string>({"1"});
  cout << "1" << endl;
  vector<string>* tmp = new vector<string>();

  while (1) {
    tmp->clear();
    tmp->push_back(vec->at(0));
    bool exit = false;
    int n = vec->size();
    for (int i = 1; i*2 <= n; ++i) {
      string res = bigadd(vec->at(i), vec->at(i - 1));
      // check maximum
      if (res.size() > MAX_SIZE) exit = true;
      tmp->push_back(res);
    }

    // mirror the vector
    int index = (n % 2 == 0) ?
      tmp->size() - 2 :   // tmp size should be odd 
      tmp->size() - 1;   // tmp size should be even
    while (index >= 0) {
      tmp->push_back(tmp->at(index));
      index--;
    }

    vector<string>* tp = tmp;
    tmp = vec;
    vec = tp;

    bool first = true;
    for (int i = 0; i < vec->size(); ++i) {
      if (first) {
        first = false;
      } else {
        cout << " ";
      }
      cout << vec->at(i);
    }
    cout << endl;
    if (exit) break;
  }
}
