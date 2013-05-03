#include <iostream>
using namespace std;
int main() {
  int n;
  string line;
  while (cin >> n) {
    getline(cin, line); 
    if (n == 0)
      break;
    int* sum = new int[n];
    int max = -1;
    for (int i = 0; i < n; ++i) {
      getline(cin, line);
      int s = 0;
      for (int j = 0; j < 25; ++j) {
        if (line[j] == 'X') 
          s++;
      }
      if (max < s)
        max = s;
      sum[i] = s;
    }
    int diff = 0;
    for (int i = 0; i < n; ++i) 
      diff += (max - sum[i]);
    cout << diff << endl;  
  }
  return 0;
}
