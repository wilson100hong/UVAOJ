#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// 2016/11/13
// STAR:
// SKILL:
// TRAP:

typedef unsigned long long ULL;

vector<map<int, int>> FACTORS;
vector<int> PRIMES;

void init() {
  // build PRIMES
  PRIMES.push_back(2);
  for (int n=3;n<1009;++n) {
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

  FACTORS.push_back({});  // 0
  FACTORS.push_back({});  // 1
  for (int n=2;n<1009;++n) {
    int x = n;
    map<int, int> factors;
    for (int p : PRIMES) {
      if (p*p > x) break;
      if (x % p == 0) {
        factors[p] = 0;
        while (x%p == 0) {
          factors[p]++;
          x /= p;
        }
      }
    }
    if (x != 1) {
      factors[x] = 1;
    }
    FACTORS.push_back(factors);
  }
}

void solve(const string& line) {
  int cur = 0;
  while (line[cur] != '!') {
    cur++;
  }
  int k = line.substr(cur).size();
  int n = stoi(line.substr(0, cur));
  map<int, int> all;
  while (n > 0) {
    map<int, int> factors = FACTORS[n];
    for (auto& p_c : factors) {
      int p = p_c.first;
      if (all.count(p) == 0) {
        all[p] = 0;
      }
      all[p] += p_c.second;
    }
    n -= k;
  }

  ULL ans = 1;
  for (auto& p_c : all) {
    int c = p_c.second;
    ULL new_ans = ans*(c+1);
    if (new_ans > 1e18 || new_ans < ans) {
      cout << "Infinity";
      return;
    }
    ans = new_ans;
  }
  cout << ans;
}

int main() {
  init();
  string line;
  int cases = 1;
  int N;
  cin >> N;
  getline(cin, line);
  while (N--) {
    getline(cin, line);
    cout << "Case " << cases++ << ": ";
    solve(line);
    cout << endl;
  }
}
