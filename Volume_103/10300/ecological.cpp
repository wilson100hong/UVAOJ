#include <iostream>
using namespace std;
int main() {
  int n;
  cin >> n;
  while (n-- > 0) {
    int f; 
    int sum = 0;
    cin >> f;
    while (f-- > 0) {
      int area, animal, env;
      cin >> area >> animal >> env;
      sum += area * env;
    }
    cout << sum << endl;
  }
  return 0;
}
