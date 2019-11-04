#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

typedef unsigned long long ULL;

ULL gcd(ULL a, ULL b) {
  if (a < b) return gcd(b, a);
  if (b == 0) return a;
  return gcd(b, a % b);
}

void solve(const vector<ULL>& numbers) {
  int n = numbers.size();
  ULL total = n * (n-1) /2;
  ULL pp = 0;
  for (int i=0;i<n;++i) {
    for (int j=i+1;j<n;++j) {
      if (gcd(numbers[i], numbers[j]) == 1) {
        pp++;
      }
    }
  }
  if (pp == 0) {
    cout << "No estimate for this data set." << endl;
  } else {
    double pi = sqrt(6.0 * (static_cast<double>(total) / pp));
    cout << fixed << setprecision(6) << pi << endl;
  }
}

int main() {
  int N;
  while (cin >> N) {
    vector<ULL> numbers;
    if (N == 0) break;
    for (int i=0;i<N;++i) {
      ULL x;
      cin >> x;
      numbers.push_back(x);
    }
    solve(numbers);
  }
}
