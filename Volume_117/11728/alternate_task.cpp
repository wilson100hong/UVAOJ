#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>

using namespace std;

constexpr int kMax = 1001;

bool IS_PRIME[kMax];
vector<int> PRIMES;


void Sift() {
  for (int i=0;i<kMax;++i) {
    IS_PRIME[i] = true;
  }
  IS_PRIME[0] = IS_PRIME[1] = false;
  for (int i=2;i < kMax;++i) {
    if (!IS_PRIME[i]) {
      continue;
    }
    PRIMES.push_back(i);
    for (int j=2*i;j<kMax;j+=i) {
      IS_PRIME[j] = false;
    }
  }
}

typedef pair<int, int> FacCnt;
vector<FacCnt> Factorize(int n) {
  vector<FacCnt> res;
  if (IS_PRIME[n]) {
    res.push_back({n, 1});
    return res;
  }

  for (int p : PRIMES) {
    if (p * p > n) break;
    int cnt = 0;
    while (n % p == 0) {
      cnt++;
      n /= p;
    }
    res.push_back({p, cnt});
  }

  if (n > 1) {
    res.push_back({n, 1});
  }
  return res;
}

typedef unsigned long long ULL;

void RecFactorSum(
    const vector<FacCnt>& factors,
    int index, ULL accum, int* sum) {
  if (index >= factors.size()) {
    // DFS leaf
    *sum = *sum + accum;
    return;
  }
  
  const auto& faccnt = factors[index];

  for (int cnt=0; cnt <= faccnt.second;++cnt) {
    RecFactorSum(factors, index + 1, accum, sum);
    accum *= faccnt.first;
  }
}

ULL FactorSum(int n) {
  int sum = 0;
  RecFactorSum(Factorize(n), 0, 1, &sum);
  return sum;
}

int ANS[kMax];

void Init() {
  // Build ANS
  for (int i=0;i<kMax;++i) {
    ANS[i] = -1;
  }

  for (int i=1;i<kMax;++i) {
    ULL ss = FactorSum(i);
    if (ss < kMax) {
      ANS[ss] = i;
    }
  }
}


int main() {
  Sift();
  Init();
  int n;
  int ca = 1;
  while (cin >> n) {
    if (n == 0) break;
    cout << "Case " << ca++ << ": " << ANS[n] << endl;
  }
}
