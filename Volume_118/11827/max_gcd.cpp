#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

typedef long long LL;

LL GCD(LL a, LL b) {
  if (a < b) return GCD(b, a);
  if (b == 0) return a;
  return GCD(b, a % b);
}

LL Solve(const vector<LL>& numbers) {
  LL ans = 1;
  for (int i=0;i<numbers.size()-1;++i) {
    for (int j=i+1;j<numbers.size();++j) {
      LL g = GCD(numbers[i], numbers[j]);
      if (g > ans) {
        ans = g;
      }
    }
  }
  return ans;
}

int main() {
  int N;
  string line;
  cin >> N;
  getline(cin, line);

  while (N--) {
    getline(cin, line);
    stringstream ss(line);
    vector<LL> numbers;
    LL x;
    while (ss >> x) {
      numbers.push_back(x);
    }
    cout << Solve(numbers) << endl;
  }
}
