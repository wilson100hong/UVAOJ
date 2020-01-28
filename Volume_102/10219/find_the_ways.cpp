// 1. Use log for digits
// 2. Stirling's formula: https://en.wikipedia.org/wiki/Stirling%27s_approximation
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cmath>
using namespace std;


// return log(n!)
double log10fac(int n) {
  return (0.5*log(2.0*n*M_PI) + n*log(n) - n) / log(10.0);
}

int Solve(int n, int k) {
  return static_cast<long long>(log10fac(n) - log10fac(k) - log10fac(n-k)) + 1;
}

int main() {
  int n, k;
  while (cin >> n >> k) {
    cout << Solve(n, k) << endl;
  }
}
