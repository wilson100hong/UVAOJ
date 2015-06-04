#include <iostream>
#include <string>
#include <vector>

using namespace std;

string i2s(int n) {
  string s = "";
  for (int i = 0; i < 5; ++i) {
    int d = n % 10;
    s = to_string(d) + s;
    n /= 10;
  }
  return s;
}

bool valid(int n, vector<bool>* seen) {
  for (int i = 0; i < 5; ++i) {
    int d = n % 10;
    if ((*seen)[d]) {
      return false;
    }
    (*seen)[d] = true;
    n /= 10;
  }
  return true;
}

bool solve(int n) {
  bool ok = false;
  int denom = 1234;
  while (denom * n <= 98765) {
    int nom = denom * n;
    vector<bool> seen(10, false);
    if (valid(nom, &seen) && valid(denom, &seen)) {
      cout << i2s(nom) << " / " << i2s(denom) << " = " << n << endl;
      ok = true;
    }
    denom++;
  }
  return ok;
}

int main() {
  int n;
  bool first = true;
  while (1) {
    cin >> n;
    if (n == 0)
      break;
    if (!first) {
      cout << endl;
    }
    if (!solve(n))
      cout << "There are no solutions for " << n << "." << endl;
    first = false;
  }
}
