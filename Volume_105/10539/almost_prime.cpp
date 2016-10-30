#include <iostream>
#include <vector>
using namespace std;

// 2016/10/29
// STAR:
// SKILL:
// TRAP:

typedef unsigned long long ULL;
vector<ULL> PRIMES;

void init() {
  // build primes up to 1e6
  PRIMES.push_back(2);
  for (ULL n=3; n<1e6; ++n) {
    bool is_prime = true;
    for (ULL p : PRIMES) {
      if (p*p > n) break;
      if (n % p == 0) {
        is_prime = false;
        break;
      };
    }
    if (is_prime) {
      PRIMES.push_back(n);
    }
  }
}

ULL solve(ULL low, ULL high) {
  ULL res = 0;
  // return how many almost-prime number in range [low, high]
  // try all primes, and count the occurence in the range
  for (ULL p : PRIMES) {
    ULL number = p*p;  // number < 1e12
    while (number < low) {
      number *= p;
    }
    while (number <= high) {
      res++;
      number *= p;
    }
  }
  return res;
}

int main() {
  init();
  int N;
  cin >> N;
  while (N--) {
    ULL low, high;
    cin >> low >> high;
    cout << solve(low, high) << endl;
  }
}
