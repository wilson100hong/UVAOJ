#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int MUL[4] = {2, 3, 5, 7};

int min(vector<ll>& list) {
  ll min = list[0];
  for (ll ele : list) {
    if (ele < min) {
      min = ele;
    }
  }
  return min;
}

// This really disgusting...
string suffix(int n) {
  if (n % 100 == 11 || n % 100 == 12 || n % 100 == 13) return "th";
  if (n % 10 == 1) return "st";
  if (n % 10 == 2) return "nd";
  if (n % 10 == 3) return "rd";
  return "th";
}

int main() {
  // init
  vector<ll> humble;
  humble.push_back(1);
  for (int cur = 1; cur < 5842; ++cur) {
    int last = cur - 1;
    ll target = humble[last];
    vector<ll> mul(4, 0);
    for (int m = 0; m < 4; ++m) {
      for (int i = last; i >= 0 && humble[i] * MUL[m] > target; --i) {
        mul[m] = humble[i] * MUL[m];
      }
    }
    humble.push_back(min(mul));
  }
  
  while (1) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    cout << "The " << n << suffix(n) << " humble number is " << humble[n - 1] << "." << endl;
  }
}

