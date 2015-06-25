#include <iostream>
using namespace std;

string DP[1001];

int max(int a, int b) {
  return a > b ? a : b;
}

string bigadd(string s1, string s2) {
  int size = max(s1.size(), s2.size()) + 1;
  string result(size, '0');
  int carry = 0; 
  for (int k = size - 1, i = s1.size() - 1, j = s2.size() - 1; k >= 0; --k, --i, --j) {
    int di = i >= 0 ? s1[i] - '0' : 0;
    int dj = j >= 0 ? s2[j] - '0' : 0;
    
    int dk = carry + di + dj;
    carry = dk / 10;
    result[k] = (dk % 10) + '0';
  }

  int start = 0;
  while (result[start] == '0' && start < size) {
    start++;
  }
  if (start > 0) {
    result = result.substr(start);
  }
  return result;
}

void init() {
  DP[0] = "1";
  DP[1] = "2";
  for (int i = 2; i <= 1000; ++i) {
    DP[i] = bigadd(DP[i - 1], DP[i - 2]);
  }
}

int main() {
  init();
  int n;
  while (cin >> n) {
    cout << DP[n] << endl;
  }
}
