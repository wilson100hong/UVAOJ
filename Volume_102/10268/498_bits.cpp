#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <sstream>

using namespace std;

typedef long long LL;

LL Solve(const vector<LL>& as, LL x) {
  vector<LL> das;
  LL base = as.size() - 1;
  for (int i=0;i<as.size()-1;++i) {
    das.push_back(as[i] * base);
    base--;
  }

  LL sum = 0;
  LL xp = 1;
  for (int i=das.size()-1;i>=0;i--) {
    sum += das[i] * xp;
    xp *= x;
  }
  return sum;
}

int main() {
  string line;
  while (getline(cin, line)) {
    stringstream ss(line);
    LL x;
    ss >> x;
    getline(cin, line);
    stringstream ss2(line);
    vector<LL> as;
    LL a;
    while (ss2 >> a) {
      as.push_back(a);
    }
    cout << Solve(as, x) << endl;
  }
}
