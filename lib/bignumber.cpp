// Bignumber arithematics.
// TODO: subtraction
// TODO: division
string strip_leading_zeros(string s) {
  int start = 0;
  while (s[start] == '0' && start < s.size()) {
    start++;
  }
  return s.substr(start);
}

string bigadd(string s1, string s2) {
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

string bigmul(string s1, string s2) {
  int size = s1.size() + s2.size();
  vector<int> buffer(size, 0);

  for (int i = s1.size() - 1; i >= 0; --i) {
    int carry = 0;
    for (int j = s2.size() - 1; j >= 0; --j) {
      int di = s1[i] - '0', dj = s2[j] - '0';
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

