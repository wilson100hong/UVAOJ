// 2016/10/07
// STAR: *
// SKILL: prime
// TRAP: emirp != prime
#include <iostream>
#include <set>
#include <vector>
using namespace std;

set<int> PRIMES;
int MAX = 1000002;

void init() {
  // TODO: build prime
  for (int i=2;i<MAX;++i) {
    bool is_prime = true;
    for (int prime : PRIMES) {
      if (prime*prime > i) break;
      if (i % prime == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      PRIMES.insert(i);
    }
  }
}

int reverse(int n) {
  int res = 0;
  while (n) {
    int d = n % 10;
    res = res*10 + d;
    n /= 10;
  }
  return res;
}

int main() {
  init();
  int n;

  while (cin >> n) {
    if (PRIMES.count(n) == 0) {
      cout << n << " is not prime." << endl;
    } else {
      int rn = reverse(n);
      if (rn !=n && PRIMES.count(rn) > 0) {
        cout << n << " is emirp." << endl;
      } else {
        cout << n << " is prime." << endl;
      }
    }
  }
}
