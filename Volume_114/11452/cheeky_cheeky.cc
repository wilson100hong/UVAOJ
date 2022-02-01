#include <iostream>
#include <vector>
using namespace std;

vector<int> build_lps(const string& s) {
  int n = s.size();
  vector<int> lps(n, 0);
  lps[0] = -1;
  int cnd = 0, pos = 1;
  while (pos < n) {
    if (s[pos] == s[cnd]) {
      lps[pos] = lps[cnd];
    } else {
      lps[pos] = cnd;
      while (cnd >= 0 && s[pos] != s[cnd]) {
        cnd = lps[cnd];
      }
    }
    cnd++;
    pos++;
  }
  return lps;
}


int find_period(const string& s) {
  vector<int> lps = build_lps(s);
  int n = s.size();
  int left = n/3 + 1, right = n/2;
  for (int p= n/3+1; p<= n/2; ++p) {
    bool good = true;
    for (int i=0;i<p;++i) {
      int j=i+p;
      if (s[i] != s[j]) {
        good = false;
        break;
      }
      int k=j+p;
      if (k <n && s[j] != s[k]) {
        good = false;
        break;
      }
    }
    if (good) return p;
  }
  // TODO: will this happen?
  cout << "-1 period" << endl;
  return -1;
}

void solve(const string& s) {
  int period = find_period(s);
  int start = s.size() % period;
  int len = 8;
  while (len--) {
    cout << s[start % period];
    start++;
  }
  cout << "..." << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    string s;
    cin >> s;
    solve(s);
  }
}
