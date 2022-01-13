#include <iostream>
#include <vector>
using namespace std;

string reverse(const string& s) {
  string r = s;
  int i=0,j=r.length()-1;
  while (i<j) {
    swap(r[i++], r[j--]);
  }
  return r;
}

vector<int> build_lps(const string& s) {
  int n = s.size();
  vector<int> lps(n, 0);
  for (int i=1;i<n;++i) {
    int j = lps[i-1];
    while (j != 0 && s[j] != s[i]) {
      j = lps[j-1];
    }

    if (s[j] == s[i]) j++;
    lps[i] = j;
  }
  return lps;
}


void solve(const string& s) {
  string r = reverse(s);
  string t = r + "?" + s;
  vector<int> lps = build_lps(t);
  string ans = s + r.substr(lps[lps.size()-1]);
  cout << ans << endl;
}

int main() {
  string s;
  while (cin >> s) {
    solve(s);
  }
}
