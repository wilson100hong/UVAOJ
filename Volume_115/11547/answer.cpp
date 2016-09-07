#include <iostream>
using namespace std;

int main() {
  int cases;
  cin >> cases;
  int n;
  while(cases--) {
    cin >> n;
    long long int num = (63*n + 7492)*5 - 498;
    if (num < 0)
      num *= -1;
    num /= 10;
    cout << num % 10 << endl;
  }
}
