#include <iostream>
using namespace std;
#define N_MAX 1000
int ary[N_MAX][N_MAX];

int max(int a, int b) {
  return a >= b ? a : b; 
}

int get(int i, int j) {
  if (i < 0 || j < 0)
    return 0;
  else
    return ary[i][j]; 
}

int main () {
  string s1, s2;
  while (getline(cin, s1)) {
    getline(cin, s2);
    int m = s1.length();
    int n = s2.length();
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (s1[j] == s2[i]) {
          ary[i][j] = get(i - 1, j - 1) + 1;  
        } else {
          ary[i][j] = max(get(i - 1, j), get(i, j - 1));
         }
      }
    }
    cout << ary[n - 1][m - 1] << endl;
  }
  return 0;
}
