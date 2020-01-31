#include <iostream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;
typedef unsigned long long ULL;

vector<ULL> PRIMES;

void Init() {
  // Build RPIMES
  PRIMES.push_back(2);
  for (int i=3;i<21;++i) {
    bool is_prime = true;

    int j = 0;
    while (PRIMES[j]*PRIMES[j] <= i) {
      if (i % PRIMES[j] == 0) {
        is_prime = false;
        break;
      }
      j++;
    }
    if (is_prime) {
      PRIMES.push_back(i);
    }
  }
}

map<int, int> Factorize(int n) {
  map<int, int> res;
  for (ULL p : PRIMES) {
    while (n % p == 0) {
      res[p]++;
      n /= p;
    }
  }
  return res;
}

map<int, int> FactorizeFactorial(int n) {
  map<int, int> factors;
  for (int i=2;i<=n;++i) {
    map<int, int> fs = Factorize(i);
    for (const auto& kv : fs) {
      factors[kv.first] += kv.second;
    }
  }
  return factors;
}

ULL Solve(const string& str) {
  map<int, int> nom_factors = FactorizeFactorial(str.size());

  map<char, int> counts;
  for (int i=0;i<str.size();++i) {
    counts[str[i]]++;
  }

  for (const auto& kv : counts) {
    map<int, int> denom_factors = FactorizeFactorial(kv.second);
    for (const auto& f_c : denom_factors) {
      nom_factors[f_c.first] -= f_c.second;
      if (nom_factors[f_c.first] < 0) cout << "STUPID " << endl;
    }
  }

  ULL res = 1;
  for (const auto& kv : nom_factors) {
    for (int i=0;i<kv.second;++i) {
      res *= kv.first;
    }
  }
  return res;
}

int main() {
  Init();
  string line;
  int TC;
  cin >> TC;
  getline(cin, line);
  for (int tc=1;tc<=TC;++tc) {
    getline(cin, line);
    cout << "Data set " << tc << ": " << Solve(line) << endl;
  }
}
