#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
  cout.setf(ios::fixed,ios::floatfield);
  cout.precision(0);
  double n, p;
  while (cin >> n >> p) {
    double sol =  pow(p, 1/n) ; 
    cout << sol << endl;
  }
  return 0;
}
