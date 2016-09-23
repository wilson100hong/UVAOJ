#include <iostream>
using namespace std;

int min(int a, int b) {
  return a < b ? a : b;
}

int diff(const string& s1, const string& s2) {
  int n = min(s1.size(), s2.size());
  int res = 0;
  for (int i=0;i<n;++i) {
    if (s1[i] != s2[i]) res++;
  }
  return res;
}

int recog(const string& str) {
  if (str.size() == 5) return 3;
  int d1 = diff(str, "one");
  int d2 = diff(str, "two");
  if (d1 < d2) return 1;
  else return 2;
}

int main() {
  string line;
  int n;
  cin >> n;
  getline(cin, line);
  while (n--) {
    getline(cin, line);
    cout << recog(line) << endl;
  }
}
