// http://en.wikipedia.org/wiki/Longest_increasing_subsequence
#include <iostream>
#include <vector>
#include <stack>
#include <utility>

using namespace std;

int main() {
  vector<int> input;
  int n;
  while (cin >> n) {
    input.push_back(n);
  }

  vector<int> len(input.size() + 1, -1);
  vector<int> pred(input.size(), -1);

  int max_len = 0;

  for (int i = 0; i < input.size(); ++i) {
    // binary search for largest index that input[len[index]] < input[i]
    int lo = 1, hi = max_len; //len.size() - 1;
    while (lo <= hi) {
      int med = (lo + hi) / 2;
      if (input[len[med]] >= input[i]) {
        hi = med - 1;
      } else {
        lo = med + 1;
      }
    }

    // lo is the new length of sub-sequence if we appended with input[i]
    // lo has minimum = 1
    int new_len = lo;
    len[new_len] = i;
    pred[i] = len[new_len - 1];

    if (new_len > max_len) {
      max_len = new_len;
    }
  }

  vector<int> ans(max_len, 0);
  int cur = len[max_len];
  for (int i = max_len - 1; i >=0; --i) {
    ans[i] = input[cur];
    cur = pred[cur];
  }

  cout << max_len << endl;
  cout << "-" << endl;
  for (const int& a : ans) {
    cout << a << endl;
  }
}
