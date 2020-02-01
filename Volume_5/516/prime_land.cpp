#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

typedef unsigned long long ULL;
vector<ULL> PRIMES;

// Build PRIMES
void Sieve() {
  PRIMES.push_back(2);
  for (ULL i = 3; i < 40000; i+=2) {
    bool is_prime = true;

    for (ULL p : PRIMES) {
      if (i % p == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) {
      PRIMES.push_back(i);
    }
  }
}

map<ULL, ULL> Factorize(ULL x) {
  map<ULL, ULL> res;
  for (ULL p : PRIMES) {
    while (x % p == 0) {
      x /= p;
      res[p]++;
    }
    if (x == 1) break;
  }
  return res;
}

int main() {
  Sieve();
  string line;
  while (getline(cin, line)) {
    if (line == "0") break;
    stringstream ss(line);
    ULL base, power;
    ULL x = 1;
    while (ss >> base) {
      ss >> power;
      while (power) {
        x *= base;
        power--;
      }
    }
    x--;

    auto factors = Factorize(x);
    bool first = true;
    for (auto it = factors.rbegin(); it != factors.rend(); ++it) {
      if (!first) cout << " ";
      first = false;
      cout << it->first << " " << it->second;
    }
    cout << endl;
  }
}
