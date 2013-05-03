#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int gcd(int a, int b) {
  if (b > a)
    return gcd(b, a);
  else if (b == 0)
    return a;
  else
    return gcd(b, a % b);
}

unsigned long long Perm(int in[26]) {
  int cnt[26];

  for (int i = 0; i < 26; ++i)
    cnt[i] = in[i];
  
  int sum = 0;
  for (int i = 0; i < 26; ++i)
    sum += cnt[i];
  vector<int> up;
  for (int i = 2; i <= sum; ++i)
    up.push_back(i);
  
  for (int i = 0;i < 26; ++i) {
    while (cnt[i] > 1) {
      int x = cnt[i];
      int j = 0;
      while (x != 1 && j < up.size()) {
        int g = gcd(x, up[j]);
        if (g == 1) {
          j++;
        } else {
          x /= g;
          up[j] /= g;
        }
      }
      cnt[i] --;
    }
  } 
  
  unsigned long long perm = 1;
  for (int i = 0; i < up.size(); ++i)
    perm *= up[i];
  return perm;
}

unsigned long long Solve(string s) {
  int len = s.length();
  vector<char> letters;
  for (int i = 0; i < len; ++i) 
    letters.push_back(s[i]);
  
  sort(letters.begin(), letters.end()); 
  int cnt[26] = {0};
  for (int i = 0; i < len; ++i)
    cnt[letters[i] - 'a']++;
  
  unsigned long long perm_total = Perm(cnt);
  unsigned long long pos = 1;
  
  int index = 0;
  while (index < len) {
    int n = len - index;
    while (letters[index] != s[index]) {
      // 1. find the first j where letters[j] > letters[index]
      int j = index + 1;
      while (j < len && letters[index] >= letters[j])
        j++;

      // 2. pos += calculate the perm from letters[index+1] .. letters[len-1]
      int z = cnt[letters[index] - 'a'];
      int g = gcd(n, z);
      int zz = z / g;
      int nn = n / g;
      unsigned long long  inc = perm_total * zz / nn;
      //cout << "INC: " << inc << endl;
      pos += inc;
      //cout << "POS: " << pos << endl;
      // 3. swap(letters[index], letters[j])
      swap(letters[index], letters[j]);
    }
    // This has precision error .... Q_Q
    int z = cnt[letters[index] - 'a'];
    int g = gcd(n, z);
    z /= g;
    n /= g;
    perm_total = (perm_total * z / n);
    cnt[letters[index] - 'a']--;
    index++;
  }
  return pos; 
}

int main() {
  string line;
  while (getline(cin, line)) {
    if (line == "#")
      break;
    cout.width(10);
    cout << Solve(line) << endl; 
  }
}
