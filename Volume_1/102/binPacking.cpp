#include <iostream>
#include <sstream>
#include <string>
using namespace std;
char symbol(int n) {
  int r = n % 3;
  switch(r) {
    case 0:
      return 'B';
    case 1:
      return 'G';
    case 2:
    default:
      return 'C';
  }
}
int main() {
  
  int  perm[6][3]= {
    {0, 5, 7},
    {0, 4, 8},
    {2, 3, 7},
    {2, 4, 6},
    {1, 3, 8},
    {1, 5, 6}
    };
  
  string line;
  int a[9];
  while(getline(cin, line)) {
    istringstream in(line, istringstream::in);
    int i = 0;
    int sum = 0;
    while(i < 9) {
      in >> a[i];
      sum += a[i];
      i++;
    }
  
    int max = -1;
    int comb = -1;
    
    for (int i = 0; i < 6; i++) {
      int part = a[perm[i][0]] + a[perm[i][1]] + a[perm[i][2]];
      if (part > max) {
        max = part;
        comb = i;
      }
    }
    for (int i = 0; i < 3; i++) {
      cout << symbol(perm[comb][i]);  
    }
    cout << " " << sum - max << endl;
  }
  return 0;
}


