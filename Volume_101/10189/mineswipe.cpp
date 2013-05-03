#include <iostream>
using namespace std;
int main() {
 int h, w;
 int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
 int dy[] = {1, -1, 1, 0, -1, 1, 0, -1};
 int field = 0;
 while (cin >> h >> w) {
  if ( h==0 && w==0) {
    break;
  }
  string line;
  getline(cin,line);  
  int** ary = new int*[h];
  for (int i=0;i<h;++i) {
    ary[i] = new int[w];
  }
  for (int i=0;i<h;++i) {
    getline(cin,line);  
    for (int j=0;j<w;++j) {
      ary[i][j] = line[j] == '*' ? 1 : 0;
    }
  }

  if (field) {
    cout << endl;  
  }
  cout  <<  "Field #" << ++field << ":" << endl;
  for (int i=0;i<h;++i) {
    for (int j=0;j<w;++j) {
      if (ary[i][j] == 1) {
        cout << "*";
      } else {
        int sum = 0;
        // loop all neighbor  
        for (int k=0;k<8;++k){
          int y = i + dy[k];
          int x = j + dx[k];
          if (0<=y && y<h && 0<=x && x<w) {
            sum+=ary[y][x];  
          } 
        }
        cout << sum;
      }
    }  
    cout <<endl;
  }
  for (int i=0;i<h;++i){
    delete ary[i];
  }
  delete ary;
 }
 
 return 0;
}
