#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define MAX 10001
bool p[MAX];
vector<int> prime;

void init() {
  for (int i = 0; i < MAX; ++i) {
    p[i] = true;
  }
  
  for (int i = 2; i < MAX; ++i) {
    if (p[i]) {
      int j = 2*i;
      prime.push_back(i);
      while (j < MAX) {
        p[j] = false;
        j += i;
      }
    }
  }
}

int divide(int n) {
  int d = 1;
  for (int i = 0; i < prime.size() && n >= prime[i]; ++i) {
    int s = 0;
    while (n % prime[i] == 0) {
      n = n / prime[i];
      s++;
    }
    d *= (s + 1);
  }
  if (n != 1)
    d *= 2;
  return d;
}

int main () {
  init();
  int round;
  cin >> round;
  int a, b;
  while (round-- > 0) {
    cin >> a >> b;
    int candidate = -1, max = -1;
    for (int i = a; i <= b; ++i) {
      int n = divide(i);
      if (n > max) {
        max = n; 
        candidate = i;
      }
    }
    cout << "Between " << a << " and " << b << ", " << candidate << " has a maximum of " << max << " divisors." << endl;
  }
  return 0;
}
