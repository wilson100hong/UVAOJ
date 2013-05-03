#include <iostream>
using namespace std;



int main() {
  int n;
  while (cin >> n) {
    int* ary = new int[n];
    for (int i = 0; i < n; ++i)
      cin >> ary[i];
    int cnt = 0;
    // Bubble sort here
    for (int i = n - 1; i >= 1; --i) {
      for (int j = 0; j < i; ++j)
        if (ary[j] > ary[j + 1]) {
          int tmp = ary[j + 1];
          ary[j + 1] = ary[j];
          ary[j] = tmp;
          cnt++;
        }
    }
//    for (int i = 0; i < n; ++i)
 //     cout << ary[i] << ",";
    cout << "Minimum exchange operations : " << cnt << endl;
  
  }
  
  return 0;
}
