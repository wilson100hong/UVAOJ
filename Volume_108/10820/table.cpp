#include <iostream>
#include <vector>
#include <set>
using namespace std;

// 2016/10/31
// STAR: *
// SKILL: Euler-Totient, prime factorization
// TRAP:

int MAX = 50001;

typedef unsigned long long ULL;
vector<int> PRIMES;
vector<int> ET(MAX, 0);
vector<ULL> TABLE(MAX, 0);

void init() {
  // build PRIMES
  PRIMES.push_back(2);
  for (int i=3;i<MAX;++i) {
    bool is_prime = true;
    for (int p : PRIMES) {
      if (p*p > i) break;
      if (i % p == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      PRIMES.push_back(i);
    }
  }
  // TODO: build ET
  for (int i=2;i<MAX;++i) {
    // factorization
    int n = i;
    set<int> factors;
    for (int p : PRIMES) {
      if (p*p > n) break;  // always pay attention!
      if (n % p == 0) {
        factors.insert(p);
        while (n % p == 0) {
          n /= p;
        }
      }
    }
    if (n != 1) {
      factors.insert(n);
    }
    n = i;
    for (int f : factors) {
      n /= f;
      n *= (f-1);
    }
    ET[i] = n;
  }

  TABLE[1] = 1;
  for (int i=2;i<MAX;++i) {
    TABLE[i] = TABLE[i-1] + 2*ET[i];
  }
}


int main() {
  init();
  int n;
  while (cin >> n) {
    if (n == 0) break;
    cout << TABLE[n] << endl;
  }
}
