#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <string>
using namespace std;

int max(int a, int b) {
  return a > b ? a : b;
}
pair<int, int> solve(const vector<int>& height, const vector<int>& width) {
  int n = height.size();
  vector<int> inc_len(n, 0);
  vector<int> dec_len(n, 0);
  int max_inc = 0;
  int max_dec = 0;
  for (int i=0;i<n;++i) {
    inc_len[i] = dec_len[i] = width[i];
    for (int j=0;j<i;++j) {
      if (height[j] > height[i]) {
        dec_len[i] = max(dec_len[i], width[i]+dec_len[j]);
      } else if (height[j] < height[i]) {
        inc_len[i] = max(inc_len[i], width[i]+inc_len[j]);
      }
    }
    max_inc = max(max_inc, inc_len[i]);
    max_dec = max(max_dec, dec_len[i]);
  }
  return {max_inc, max_dec};
}


int main() {
  int cases;
  cin >> cases;
  for (int cs=1;cs<=cases;++cs) {
    int n;
    cin >> n;
    vector<int> height(n, 0);
    vector<int> width(n, 0);
    for (int i=0;i<n;++i) {
      cin >> height[i];
    }
    for (int i=0;i<n;++i) {
      cin >> width[i];
    }
    int inc, dec;
    cout << "Case " << cs << ".";
    tie(inc, dec) = solve(height, width);
    string inc_str = " Increasing (" + to_string(inc) + ").";
    string dec_str = " Decreasing (" + to_string(dec) + ").";
    if (inc >= dec) {
      cout << inc_str << dec_str << endl;
    } else {
      cout << dec_str << inc_str << endl;
    }
  }
}
