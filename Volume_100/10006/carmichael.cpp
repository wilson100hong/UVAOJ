#include <iostream>
#include <cmath>
using namespace std;
#define N_MAX 65000
bool prime[N_MAX];
void init() {
  int n = sqrt(N_MAX);
  for (int i = 2; i < N_MAX; ++i)
    prime[i] = true;
  for (int i = 2; i < N_MAX; ++i) {
    if (prime[i]) {
      int j = 2 * i;
      while (j < N_MAX) {
        prime[j] = false;
        j += i;
      }
    }
  }
}

// b ^ pow mod n
int powmod(int b, int pow, int n) {
  long long a = b % n;
  int r = 1;
  while (pow > 0) {
    if (pow & 1) {
      r = (r * a) % n;
    }
    a = (a * a) % n;
    pow = pow >> 1;
  }
  return r;
}

int main () {
  init();
  int n;
  while (cin >> n) {
    if (n == 0)
      break;
    bool carmichael = true;
    if (prime[n]) {
       carmichael = false;
    } else {
      // its prime
      for (int i = 2; i < n; ++i) {
        if (powmod(i, n, n) != i) {
          carmichael = false;
          break;
        }
      }
      // its prime and pass carmichael test
    }
    if (carmichael)
      cout << "The number " << n << " is a Carmichael number." << endl;
    else 
      cout << n << " is normal." << endl;
  }
  return 0;
}
