#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long int ULL;

#define MAX 100000000

// record all primes < sqrt(1e9)
vector<ULL> primes;

bool is_prime(ULL x) {
  if (x == 1) return false;
  for (ULL prime : primes) {
    if (prime == x || prime * prime > x) return true;
    if (x % prime == 0) {
      return false;
    }
  }
  return true;
}

void init() {
  primes.push_back(2);
  for (ULL x = 3; x * x < MAX; x += 2) {
    if (is_prime(x)) {
      primes.push_back(x);
    }
  }
}

int get_left(ULL n) {
  int sum = 0;
  while (n > 0) {
    sum += (n % 10);
    n /= 10;
  }
  return sum;
}

// n is not prime!
int get_right(ULL n) {
  vector<ULL> factors;
  while (1) {
    bool is_prime = true;
    for (ULL prime : primes) {
      if (prime == n || prime * prime > n) break;
      if (n % prime == 0) {
        factors.push_back(prime);
        n /= prime;
        is_prime = false;
        break;
      }
    }

    if (is_prime) {
      factors.push_back(n);
      break;
    }
  }
  int sum = 0;
  for (ULL factor : factors) {
    sum += get_left(factor);
  }
  return sum;
}

void solve(ULL n) {
  ULL cur = n + 1;
  while (1) {
    if (!is_prime(cur) && get_left(cur) == get_right(cur)) {
      break;
    }
    cur++;
  }
  cout << cur << endl;
}

int main() {
  init();
  int round;
  cin >> round;
  while (round-- > 0) {
    ULL n;
    cin >> n;
    solve(n);
  }
}
