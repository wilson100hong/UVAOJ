#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;

constexpr ULL kMax = 1000001;

// Is compound; Is not prime
ULL IS_COMP[kMax] = {0};   // ==0 prime, ==1 not prime

vector<ULL> PRIMES;
// Build PRIMES
void Sift() {
  for (int i=2;i<kMax;++i) {
    if (IS_COMP[i] == 1) {
      continue;
    }
    PRIMES.push_back(i);
    for (int j=2*i;j<kMax;j+=i) {
      IS_COMP[j] = 1;
    }
  }
}

map<ULL, int> Factorize(ULL n) {
  if (!IS_COMP[n]) {
    return {{n, 1}};
  }
  map<ULL, int> factors;
  for (ULL p : PRIMES) {
    if (p*p > n) break;
    while (n % p == 0) {
      n /= p;
      factors[p]++;
    }
  }
  if (n != 1) {
    factors[n]++;
  }
  return factors;
}

vector<ULL> ANS;

void Init() {
  map<ULL, int> lcm;
  ANS.push_back(0);  // ANS[0] = 0
  ANS.push_back(1);  // ANS[1] = 1

  int ans_except_25 = 1;

  for (ULL i=2;i<kMax;++i) {
    ULL n = i;
    map<ULL, int> factors = Factorize(n);


    for (const auto& kv: factors) {
      ULL p = kv.first;
      int remain = kv.second;
      if (lcm.count(p)) {
        remain = std::max(0, remain - lcm[p]);
      }
      while (remain--) {
        if (p != 2 && p != 5) {
          ans_except_25 *= p;
          ans_except_25 %= 10;
        }
        lcm[p]++;
      }
    }

    int ans = ans_except_25;
    int two_count = lcm.count(2) ? lcm[2] : 0;
    int five_count = lcm.count(5) ? lcm[5] : 0;
    if (two_count > five_count) {
      int cnt = (two_count - five_count) % 4;
      if (cnt == 0) cnt = 4;
      while (cnt--) {
        ans *= 2;
        ans %= 10;
      }
    } else if (five_count > two_count) {
      ans *= 5;
      ans %= 10;
    }
    ANS.push_back(ans);
  }
}

int main() {
  Sift();
  
  Init();
  ULL x;
  while (cin >> x) {
    if (x == 0) break;
    cout << ANS[x] << endl;
  }
}
