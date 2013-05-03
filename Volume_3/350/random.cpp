#include <iostream>
using namespace std;
int main () {
  int z, i, m, l;
  int count = 1;
  while(cin >> z >> i >> m >> l) {
    if (z == i && i == m && m == l && l == 0)
      break;
    z %= m;
    int* hash = new int[m];
    for (int j = 0; j < m; ++j) {
      hash[j] = 0;
    }
    int step = 1;
    hash[l] = step++;
    
    while (1) {
      int next = (z * l + i) % m;
      if (hash[next] != 0) {
        cout << "Case " << count << ": " << step - hash[next] << endl;
        break;
      }
      hash[next] = step++;
      l = next;
    }
    delete hash;
    count++;
  }

  return 0;
}
