#include <iostream>
#include <sstream>
typedef long long int LL;
using namespace std;

int c2i(char c) {
  if ('0' <= c && c <= '9') {
    return c - '0';
  } 
  return c - 'A' + 10;
}

char i2c(int n) {
  if (0 <= n && n <= 9) {
    return n + '0';
  }
  return  n - 10 + 'A';
}

string c2s(char c) {
  stringstream ss;
  ss << c;
  return ss.str();
}

string padding7(const string& s) {
  if (s.size() == 0) return "      0";
  if (s.size() > 7) return "  ERROR";
  string result(7 - s.size(), ' ');
  return result + s;
}

string solve(const string& input, int from_base, int to_base) {
  LL number = 0;
  for (int i = 0; i < input.size(); ++i) {
    int n = c2i(input[i]);
    number = number* from_base + n;
  }

  string result; 
  while (number > 0) {
    int n = number % to_base; 
    result = c2s(i2c(n)) + result;
    number /= to_base;
  }
  return padding7(result);
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    string input;
    int from_base, to_base;
    ss >> input >> from_base >> to_base;
    cout << solve(input, from_base, to_base) << endl;
  }
}
