#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int gcd(int a, int b) {
  if (a < b) return gcd(b, a);
  if (b == 0) return a;
  return gcd(b, a % b);
}

int main() {
  while (1) {
    vector<int> inputs;
    int n;
    while (1) {
      cin >> n;
      if (n == 0) {
        break;
      } else {
        inputs.push_back(n);
      }
    }
    if (inputs.size() == 0) {
      break;
    }

    sort(inputs.begin(), inputs.end());
    vector <int> normalized;
    for (int i = 1; i < inputs.size(); ++i) {
      normalized.push_back(inputs[i] - inputs[0]);
    }
    int ans = normalized[0];
    for (int i = 1; i < normalized.size(); ++i) {
      ans = gcd(ans, normalized[i]);
    }
    cout << ans << endl;
  }
}
