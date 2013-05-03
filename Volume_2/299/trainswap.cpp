#include <iostream>
using namespace std;
int main(){
  int round;
  cin >> round;
  while (round-- > 0) {
    int l;
    cin >> l;
    int* train = new int[l];
    int i = 0;
    int cnt = 0;
    while(i < l) {
      cin >> train[i++];
    }
    for (i=0;i<l-1;++i) {
      for (int j=i+1;j<l;++j) {
        if (train[i] > train[j]) {
          // swap
          int tmp = train[i];
          train[i] = train[j];
          train[j] = tmp;
          cnt++;
        }
      }  
    }
    /*
    for (i=0;i<l;++i) {
      cout << train[i];  
    }
    cout << endl;
    */
    cout << "Optimal train swapping takes " << cnt << " swaps." << endl;
  }
  return 0;
}
