#include <iostream>
using namespace std;
int main() {
  int c;
  cin >> c;
  cout.setf(ios::fixed,ios::floatfield); 
  cout.precision(3);
  while (c-- > 0) {
    int n;
    cin >> n;
    int* score = new int[n];
    int i = 0;
    float sum = 0;
    for (i=0;i<n;++i) {
      cin >> score[i];
      sum+=score[i];
    }
    // test
    /*for (i=0; i<n; ++i) {
      cout << score[i];  
    }
    cout << endl;
    */
    float avg = (float)sum / n;
    int aa = 0;
    for (i=0; i<n; ++i) {
      if (score[i] > avg) {
        aa++;  
      }
    }
    cout << (float) aa * 100 / n << "%" << endl;
    delete score;
    string line;
    getline(cin, line);
  }
  return 0;
}
