#include <iostream>
#include <cmath>
#include <map>
using namespace std;

typedef unsigned long long ULL;

map<int, ULL> ANS;

void Init() {
  double x = 4 * log(2); // 2^ power * log(2)
  int n = 1;
  double sum_ln = 0;
  for (int power=2; power<=22; power++) {
    // sum(ln(n)) < x <= sum(ln(n+1))
    while (sum_ln < x) {
      n++;
      sum_ln += log(n);
    }
    ANS[power] = n - 1;
    x *=2;
  }
}

int main() {
  Init();

  int year;
  while (cin >> year) {
    if (year == 0) break;
    int power = (year - 1960)/10 + 2;
    cout << ANS[power] << endl;
  }
}
