#include <iostream>
#include <vector>
using namespace std;

// 2016/10/31
// STAR: *
// SKILL: prime factorization
// TRAP: 1) always terminate factorization when p*p > n

vector<int> PRIMES;

#define MAX 1e6+1

vector<bool> HAS_SQUARE(MAX, false);
vector<int> NUM_PRIMES(MAX, 0);

vector<int> MU(MAX, 0);
vector<int> M(MAX, 0);

void init() {
  PRIMES.push_back(2);
  // get all primes from [2, 1e6]
  for (int n=3;n<=MAX;++n) {
    bool is_prime = true;
    for (int p : PRIMES) {
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

  // build MU
  MU[1] = 1; 
  for (int i=2;i<MAX;++i) {
    int n = i;
    for (int p : PRIMES) {
      if (p*p > n) break;
      if (n % p == 0) {
        NUM_PRIMES[i]++;
        int cnt = 0;
        while (n % p == 0) {
          n /= p;
          cnt++;
        }
        if (cnt > 1) {
          HAS_SQUARE[i] = true;
        }
      }
    }
    if (n != 1) {
      NUM_PRIMES[i]++;  // it is prime itself
    }
    if (HAS_SQUARE[i]) {
      MU[i] = 0;
    } else {
      if (NUM_PRIMES[i] % 2 == 0) {
        MU[i] = 1;
      } else {
        MU[i] = -1;
      }
    }
  }

  // build M
  M[1] = 1;
  for (int n=2;n<MAX;++n) {
    M[n] = MU[n] + M[n-1];
  }
}

int main() {
  init();
  int n;
  while (cin >> n) {
    if (n==0) break;
    cout.width(8);
    cout << n;
    cout.width(8);
    cout << MU[n];
    cout.width(8);
    cout << M[n] << endl;
  }
}
