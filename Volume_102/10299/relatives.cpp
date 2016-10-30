#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

// 2016/10/29
// STAR: **
// SKILL: Euler Totient function
// TRAP: 1) init range should be pick 1e5
//       2) when doing factorizing, you need iteratlively divide by primes

typedef unsigned long long ULL;

vector<ULL> PRIMES;

void init() {
  // generate primes in [2, 1e5]
  PRIMES.push_back(2);
  // WA
  for (ULL n=3;n<=1e5;++n) {
    bool is_prime = true;
    for (ULL p : PRIMES) {
      if (p*p > n) break;
      if (n % p == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      PRIMES.push_back(n);
    }
  }
}

vector<ULL> factorize(ULL n) {
  vector<ULL> res;
  for (ULL p : PRIMES) {
    if (p*p > n) break;
    if (n % p == 0) {
      res.push_back(p);
      while (n % p == 0) {
        n /= p;
      }
    }
  }
  // here, n could be prime that > 1e5
  if (n != 1) {
    res.push_back(n);
  }
  return res;
}

int main() {
  init();
  ULL n;
  while (cin >> n) {
    if (n==0) break;
    if (n==1) {
      cout << 0 << endl;
      continue;
    }

    vector<ULL> facts = factorize(n);
    // Eluer Totient function
    for (ULL f : facts) {
      n /= f;
    }
    for (ULL f : facts) {
      n *= (f-1);
    }
    cout << n << endl;
  }
}
