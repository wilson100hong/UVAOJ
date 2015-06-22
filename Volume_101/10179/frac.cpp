#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef long long int ll;

vector<int> PRIMES;

void init() {
  bool cand[32000];
  for (int i = 0; i < 32000; ++i) {
    cand[i] = true;
  }
  for (int i = 2; i < 32000; ++i) {
    if (cand[i]) {
      PRIMES.push_back(i);
      int j = i + i;
      while (j < 32000) {
        cand[j] = false;
        j += i;
      }
    }
  }
}

vector<int> factorize(ll n) {
  vector<int> result;
  // factors < 32000
  for (int prime : PRIMES) {
    if (n % prime == 0) {
      result.push_back(prime);
      while (n % prime == 0) {
        n /= prime;
      }
    }
  }
  // factor >= 32000: can only be one 
  if (n != 1) {
    result.push_back(n);
  }
  return result;
}

int main() {
  init();
  while (1) {
    ll n;
    cin >> n;
    if (n == 0) {
      break;
    }
    vector<int> factors = factorize(n);
    for (int f : factors) {
      n = n / f * (f - 1);
    }
    cout << n << endl;
  }
}
