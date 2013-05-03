#include <iostream>
using namespace std;
int main() {
  int n;
  
  while(cin >> n) {
    if (n == 0)
      break;
    int* rows = new int[n];
    int* cols = new int[n];
    for (int i = 0; i < n; ++i) {
      rows[i] = 0;  
      cols[i] = 0;
    }
    int a;
   // int** ary = new int*[n];
    for (int i = 0; i < n; ++i) {
    //  ary[i] = new int[n];
      for (int j = 0; j < n; ++j) {
        //cin >> ary[i][j];  
        cin >> a;
        rows[i] += a;
        rows[i] %= 2;
        cols[j] += a;
        cols[j] %= 2;
      }
    }
    
    int rowErr = 0, colErr = 0, row = -1, col = -1;
    for (int i = 0; i < n; ++i) {
      if (rows[i] != 0) {
        rowErr++;
        row = i;
      }
      if (cols[i] != 0) {
        colErr++;
        col = i;
      }
    }
    if (rowErr == 0 && colErr == 0) {
      cout << "OK" << endl;  
    } else if (rowErr == 1 && colErr == 1) {
      cout << "Change bit (" << row + 1 << "," << col + 1 << ")" << endl;  
    } else {
      cout << "Corrupt" << endl;  
    }
    // test
    /*for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) 
        cout << ary[i][j] ;
      cout << endl;
    
    }*/
    




    delete rows;
    delete cols;
  }
  
  return 0;
}
