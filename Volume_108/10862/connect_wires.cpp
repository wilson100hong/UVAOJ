#include <iostream>
#include <vector>

using namespace std;

// 2016/11/13
// STAR: *
// SKILL: DP, big number
// TRAP: 1) formula is wrong

int max(int a, int b) {
  return a > b ? a : b;
}

string bigadd(const string& s1, const string& s2) {
  int n1 = s1.size(), n2 = s2.size();
  int n = max(n1, n2) + 1;
  string res(n, '0');

  int carry = 0;
  for (int i=0;i<res.size();++i) {
    int d1 = n1-1-i>=0 ? s1[n1-1-i]-'0' : 0;
    int d2 = n2-1-i>=0 ? s2[n2-1-i]-'0' : 0;
    int dr = d1 + d2 + carry;
    carry = dr/10;
    dr%=10;
    res[res.size()-1-i] = dr+'0';
  }
  // strip leading zero
  int cur = 0; 
  while (res[cur] == '0' && cur < res.size()) {
    cur++;
  }
  if (cur==res.size()) {
    return "0";
  }
  return res.substr(cur);
}

vector<string> SUM;  // SUM[n] = ANS[n] + ANS[n-1] + ... ANS[0]
vector<string> ANS;
void init() {
  ANS.push_back("1");
  ANS.push_back("1");  // n=1, ans = 1
  ANS.push_back("3");  // n=2, ans = 3

  SUM.push_back("1");
  SUM.push_back("2");
  SUM.push_back("5");

  for (int n=3;n<=2000;++n) {
    // a[n] = 2*(a[n-1] + a[n-2])
    string ans = bigadd(bigadd(ANS[n-1], ANS[n-1]), SUM[n-2]);
    ANS.push_back(ans);
    SUM.push_back(bigadd(ans, SUM[n-1]));
  }
}

int main() {
  init();
  int n;
  while (cin >> n) {
    if (n==0) break;
    cout << ANS[n] << endl;
  }
}
