#include <iostream>

using namespace std;

int max1d(int ary[], int len) {
  int maxEndHere = ary[0];
  int maxSoFar = ary[0];
  for (int i = 1; i < len; ++i) {
    maxEndHere += ary[i];
    if (maxEndHere < ary[i]) {
      maxEndHere = ary[i];  
    }
    if (maxEndHere > maxSoFar) {
      maxSoFar = maxEndHere;  
    }
  }
  return maxSoFar;
}

int max2d(int ary[], int n) {
  // sum[k] is the summation of ary[i][k] + ... +  ary[j][k]
  int* sum = new int[n];
  int max = ary[0];
  for (int i = 0; i < n; ++i) {
    // Reset sum
    for (int k = 0; k < n; ++k) {
      sum[k] = 0;
    }

    for (int j = i; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        sum[k] += ary[j * n + k];  
      }
      int maxsofar = max1d(sum, n);
      if (maxsofar > max) {
        max = maxsofar;  
      }
    }  
  }
  return max;
}

int main() {
  int n;
  cin >> n;
  int n2 = n * n;
  int* ary = new int[n2];
  int i = 0;
  while (i < n2) {
    cin >> ary[i++];
  }
  cout << max2d(ary, n) << endl;
  
  return 0;
}
