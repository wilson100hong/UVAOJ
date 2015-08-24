#include <iostream>
#include <string>

#define CMAX 100
#define NO_PATH -1
using namespace std;

int DEB[CMAX][CMAX];

int max(int a, int b) {
  return a > b ? a : b;
}

int min(int a, int b) {
  return a < b ? a : b;
}

int main() {
  int C, S, Q, T = 1;
  while (1) {
    cin >> C >> S >> Q;
    if (C == 0 && S == 0 && Q == 0)
      break;

    // init
    for (int i = 0; i < C; ++i)
      for (int j = 0; j < C; ++j)
          DEB[i][j] = (i == j ? 0 : NO_PATH);

    int from, to, noise;
    while (S-- > 0) {
      cin >> from >> to >> noise;
      from--; to--;
      DEB[to][from] = DEB[from][to] = noise;
    }

    // floyd warshall
    for (int k = 0; k < C; ++k) {
      for (int i = 0; i < C; ++i) {
        for (int j = 0; j < C; ++j) {
          if (DEB[i][k] != NO_PATH && DEB[k][j] != NO_PATH) {
            int tmp = max(DEB[i][k], DEB[k][j]);
            DEB[i][j] = (DEB[i][j] == NO_PATH ? tmp : min(DEB[i][j], tmp));
          }
        }
      }
    }
    
    if (T != 1) 
      cout << endl;
    cout << "Case #" << T++ << endl;
    while (Q-- > 0) {
      cin >> from >> to;
      from--; to--;
      cout << (DEB[from][to] == NO_PATH ? "no path" : to_string(DEB[from][to])) << endl;
    }
  }
}
