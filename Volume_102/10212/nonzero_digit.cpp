#include <iostream>
using namespace std;

// 2016/11/10
// STAR:
// SKILL: factorization
// TRAP:


struct Factors {
  int two;
  int five;
  int rest;  // the rest % 10
};

Factors factorize(int n) {
  int two = 0;
  while (n % 2 == 0) {
    n/=2;
    two++;
  }
  int five = 0;
  while (n % 5 == 0) {
    n/=5;
    five++;
  }
  return {two, five, n%10};
}

int min(int a, int b) {
  return a < b ? a : b;
}


int solve(int N, int M) {
  // P(N, M) = N!/(N-M)! = N*(N-1)*(N-2)*..*(N-M+1)
  int two = 0, five = 0, rest = 1;
  for (int n=N;n>(N-M);--n) {
    Factors fs = factorize(n);
    two += fs.two;
    five += fs.five;
    rest = (rest * fs.rest) % 10;

    int m = min(two, five);
    two -= m;
    five -= m;
  }
  for (int i=0;i<two;++i) {
    rest = (rest*2) % 10;
  }
  for (int i=0;i<five;++i) {
    rest = (rest*5) % 10;
  }
  return rest;
}

int main() {
  int N, M;
  while (cin >> N >> M) {
    cout << solve(N, M) << endl;
  }
}
