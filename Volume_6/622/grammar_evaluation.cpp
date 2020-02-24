// NOTE:
// 1. Leading zeros are accepted.
// 2. Care overflow.
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <limits>
using namespace std;

#define ERROR -1
constexpr int kIntMax = numeric_limits<int>::max();

bool IsDigit(char c) {
  int x = c - '0';
  return 0<=x && x<=9;
}

int ParseExpression(const string&, int*);
int ParseComponent(const string&, int*);
int ParseFactor(const string&, int*);

int ParseExpression(const string& str, int* cur) {
  if (*cur == str.size()) {
    return ERROR;
  }

  int ans = ParseComponent(str, cur);
  if (ans == ERROR) {
    return ERROR;
  }

  if (*cur == str.size() || str[*cur] != '+') {
    return ans;
  }

  (*cur)++;  // Skip '+'
  int ans2 = ParseExpression(str, cur);
  if (ans2 == ERROR) {
    return ERROR;
  }

  return ans + ans2;
}

int ParseComponent(const string& str, int* cur) {
  if (*cur == str.size()) {
    return ERROR;
  }

  int ans = ParseFactor(str, cur);
  if (ans == ERROR) {
    return ERROR;
  }

  if (*cur == str.size() || str[*cur] != '*') {
    return ans;
  }

  (*cur)++;  // Skip '*'
  int ans2 = ParseComponent(str, cur);
  if (ans2 == ERROR) {
    return ERROR;
  }

  return ans * ans2;
}

int ParseFactor(const string& str, int* cur) {
  //cout << "ParseFactor() " << str.substr(*cur) << endl;
  if (*cur == str.size()) {
    return ERROR;
  }
  if (str[*cur] == '(') {
    (*cur)++;
    int ans = ParseExpression(str, cur);
    if (ans == ERROR) {
      return ERROR;
    }
    if (*cur >= str.size() || str[*cur] != ')') {
      return ERROR;
    }
    (*cur)++;
    return ans;
  } else if (IsDigit(str[*cur])) {
    int ans = 0;
    bool leading_zero = (str[*cur] == '0');
    while (IsDigit(str[*cur])) {
      if (ans > kIntMax / 10) {
        // Overflow
        return ERROR;
      }
      int temp = ans * 10 + (str[*cur] - '0');

      if (temp < ans) {
        // Overflow
        return ERROR;
      }
      ans = temp;
      (*cur)++;
    }

    return ans;
  } else {
    return ERROR;
  }
}


int Solve(const string& str) {
  int cur = 0;
  int ans = ParseExpression(str, &cur);
  if (cur != str.size()) {
    return ERROR;
  }
  if (ans < 0) {
    return ERROR;
  }
  return ans;
}

int main() {
  int N;
  cin >> N;
  string line;
  getline(cin, line);  // eat the line for N.

  while (N--) {
    getline(cin, line);
    int ans = Solve(line);
    if (ans == -1) {
      cout << "ERROR" << endl;
    } else {
      cout << ans << endl;
    }
  }
}
