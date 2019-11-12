#include <iostream>
#include <iomanip>
using namespace std;


int gcd(int a, int b) {
  if (a < b) return gcd(b, a);
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  int step, mod;
  while (cin >> step) {
    cin >> mod;
    cout << fixed << setw(10) << step << setw(10) << mod;
    cout << "    ";
    bool good = gcd(step, mod) == 1;
    if (good) {
      cout << "Good Choice";
    } else {
      cout << "Bad Choice";
    }
    cout << endl << endl;
  }
}
