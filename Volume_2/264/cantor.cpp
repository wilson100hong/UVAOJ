#include <iostream>
using namespace std;
int main() {
  int m;
  while (cin >> m) {
    int n = 1;
    while (n * (n + 1) / 2 < m)
      n++;
    // now n * (n + 1) / 2 >= m
    int x = m - (n * (n - 1) / 2);
    cout << "TERM " << m << " IS ";
    if (n % 2 == 1)
      cout << n - (x - 1) << "/" << 1 + (x - 1) << endl;
    else
      cout << 1 + (x - 1) << "/" << n - (x - 1) << endl;

  }

  return 0;
}
