#include <iostream>
#include <vector>
using namespace std;

int solve(const vector<int>& cars) {
  int n = cars.size();
  vector<int> inc(n, 0);
  vector<int> dec(n, 0);
  // build inc and dec
  for (int i=n-1;i>=0;--i) {
    inc[i] = dec[i] = 1;
    for (int j=n-1;j>i;--j) {
      // 1. inc
      if (cars[j] > cars[i]) {
        if (inc[j]+1 > inc[i]) {
          inc[i] = inc[j]+1;
        }
      }
      // 2. dec
      else if (cars[j] < cars[i]) {
        if (dec[j]+1 > dec[i]) {
          dec[i] = dec[j]+1;
        }
      }
    }
  }
  /*
  for (int i=0;i<n;++i) {
    cout << inc[i] << ", " << dec[i] << endl;
  }
  */
  int longest = 0;
  for (int i=0;i<n;++i) {
    int len = inc[i] + dec[i] - 1;
    if (len > longest) {
      longest = len;
    }
  }
  return longest;
}

int main() {
  int cases;
  cin >> cases;
  while (cases--) {
    int n;
    cin >> n;
    vector<int> cars(n, -1);
    for (int i=0;i<n;++i){
      cin >> cars[i];
    }
    cout << solve(cars) << endl;
  }
}
