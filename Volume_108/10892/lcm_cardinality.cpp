#include <iostream>
#include <vector>
#include <map>
using namespace std;

// 2016/10/30
// STAR: *
// SKILL: prime factorization, combination
// TRAP:

typedef unsigned long long ULL;

vector<ULL> PRIMES;

void init() {
  // build PRIMES up to 1e5
  PRIMES.push_back(2);
  for (ULL n=3;n<1e5;++n) {
    bool divided = false;
    for (ULL p : PRIMES) {
      if (n % p == 0) {
        divided = true;
        break;
      }
    }
    if (!divided) {
      PRIMES.push_back(n);
    }
  }
}

map<ULL, int> factorize(ULL n) {
  // return map<prime_factor, power> 
  map<ULL, int> res;
  for (ULL p: PRIMES) {
    if (n % p == 0) {
      res[p] = 0;
      while (n % p == 0) {
        n /= p;
        res[p]++;
      }
    }
  }
  if (n != 1) {
    res[n] = 1;
  }
  return res;
}

ULL solve(ULL n) {
  map<ULL, int> factors = factorize(n);

  int np = factors.size();
  if (np == 0) return 1;  // 1

  // power+1 of each factor
  // it means you can try f^0, f^1, ...f^p
  vector<ULL> power(np, 0);

  // comb is the number of all pairs for (a, b) where
  // a, b <= power[i] and max(a, b) = power[i]
  vector<ULL> comb(np, 0);
  int idx = 0;
  for (const auto& f_p : factors) {
    power[idx] = f_p.second;
    comb[idx] = 2*power[idx]+1;
    idx++;
  }

  // mul[i] = comb[i]*comb[i+1]*..*comb[np-1]
  vector<ULL> mul(np, 0);
  mul[np-1] = comb[np-1];
  for (int i=np-2;i>=0;--i) {
    mul[i] = comb[i]*mul[i+1];
  }

  // for example, 1800 = 2^3 * 3^2 * 5^2
  // first round, we try (8,1), (8,2), (8,4) for 2; and all possible pairs in 3 & 5
  // second round is (8,8) for 2. We then try (9,1), (9,3) and all possible pairs in 5
  // last round is (8,8) and (9,9), we try all non-dup pairs for 5.
  // non-dup pairs only counts (a,b) and (b,a) once when a!=b
  ULL res = 0;
  for (int i=0;i<np;++i) {
    if (i == np-1) {
      res += (power[i]+1);
    } else {
      res += (power[i])*mul[i+1];
    }
  }
  return res;

}

int main() {
  init();
  ULL n;
  while (cin >> n) {
    if (n == 0) break;
    cout << n << " " << solve(n) << endl;
  }
}
