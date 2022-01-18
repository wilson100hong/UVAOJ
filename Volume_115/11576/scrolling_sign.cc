#include <iostream>
#include <vector>
using namespace std;

// max longest common of s1 prefix and s2 suffix
int max_lps(const string& s1, const string& s2) {
  string s = s1 + "?" + s2;
  int n = s.size();
  vector<int> lps(n, 0);

  for (int i=1;i<n;++i) {
    int len = lps[i-1];
    while (len != 0 && s[len] != s[i]) {
      len = lps[len-1];
    }
    
    if (s[i] == s[len]) {
      len++;
    }

    lps[i] = len;
  }

  //for (int i=0;i<n; ++i) {
    //cout << lps[i] << "," ;
  //}
  //cout << endl;

  return lps[n-1];
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int K, W;
    cin >> K >> W;
    string ans = "";
    string p;
    for (int i=0;i<W;++i) {
      string s;
      cin >> s;
      int overlap = 0;
      if (i > 0) {
        overlap = max_lps(s, p);
      }
      //cout << "overlap: " << overlap << endl;
      ans += s.substr(overlap);
      //cout << "ans size: " << ans.size() << endl;
      p = ans.substr(ans.size() - K);
    }
    cout << ans.size() << endl;
  }
}
