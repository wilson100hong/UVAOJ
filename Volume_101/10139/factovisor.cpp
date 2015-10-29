#include <iostream>
#include <vector>
#include <limits>
#include <map>
#include <set>

using namespace std;
#define MAX 2147483647

typedef long long int LL;
typedef map<LL, int> Factors;
set<LL> primes = {2};

// update primes to sqrt(limit)
void update_primes_to_sqrt_of(LL limit) {
  for (LL num = 3; num * num <= limit; num += 2) {
    bool is_prime = true;
    for (LL prime : primes) {
      if (prime * prime > num) break;
      if (num % prime == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime) primes.insert(num);
  }
}

// Return empty Factors when num == 1
// Return num itself when num is prime
Factors factorize(LL num) {
  Factors result;
  LL cur = num;
  for (LL prime : primes) {
    if (cur == 1) break;
    // factorize by try all primes <= sqrt(num)
    if (cur % prime == 0) {
      result[prime] = 0;
      while (cur % prime == 0) {
        result[prime]++;
        cur /= prime;
      }
    }
  }

  if (cur != 1) {
    // cur is prime
    result[cur] = 1;
  }
  return result;
}

int min(int a, int b) {
  return a < b ? a : b;
}

bool solve(LL n, LL m) {
  if (m <= n) return true;
  Factors fm = factorize(m);
  for (auto& f_c : fm) {
    LL factor = f_c.first;
    int cnt = f_c.second;
    LL cursor = factor;  // to eliminate number of cnt of factor, start cursor at "factor"
    while (cnt > 0 && cursor <= n) {
      LL rest = cursor;
      while (cnt > 0 && rest % factor == 0) {
        cnt--;
        rest /= factor;
      }
      cursor += factor;
    }
    if (cnt > 0) return false;
  }
  return true;
}

int main() {
  LL n, m;
  // init
  update_primes_to_sqrt_of(MAX);

  while (cin >> n) {
    cin >> m;
    if (solve(n, m)) {
      cout << m << " divides " << n << "!" << endl;
    } else {
      cout << m << " does not divide " << n << "!" << endl;
    }
  }
}
