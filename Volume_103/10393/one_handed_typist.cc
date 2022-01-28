#include <iostream>
#include <vector>
#include <set>
using namespace std;

string FINGERS[] = {
 "", 
 "qaz", 
 "wsx",
 "edc", 
 "rfvtgb",
 " ",
 " ",
 "yhnujm", 
 "ik,", 
 "ol.",
 "p;/"
};

int main() {
  int F, N;
  while (cin >> F >> N) {
    set<char> cannot_type;
    for (int i=0;i<F;++i) {
      int f;
      cin >> f;
      for (char c : FINGERS[f]) {
        cannot_type.insert(c);
      }
    }

    set<string> able;
    int max_len = 0;
    for (int i=0;i<N;++i) {
      string word;
      cin >> word;
      bool can_type = true; 
      for (char c : word) {
        if (cannot_type.count(c) != 0) {
          can_type = false;
          break;
        }
      }
      if (can_type) {
        able.insert(word);
        if (max_len < word.size()) {
          max_len = word.size();

        }
      }
    }
    vector<string> ans;
    for (const auto& s : able) {
      if (s.size() == max_len) {
        ans.push_back(s);
      }
    }

    cout << ans.size() << endl;
    for (const auto& s : ans) {
      cout << s << endl;
    }
  }
}
