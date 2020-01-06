#include <iostream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

int c2i(char c) {
  return c - '0';
}

int Total(const map<int, int>& counts) {
  int total = 0;
  for (const auto& kv : counts) {
    total += kv.second;
  }
  return total;
}

string Padding(int level) {
  string s = "";
  for (int i=0;i<level;++i) {
    s += "  ";
  }
  return s;
}

bool Play(int sum, map<int, int>& counts) {
  // sum % 3 == 0, can only pick 0, 3, 6, 9  from counts
  int candidates = 0;
  for (const auto& kv : counts) {
    if (kv.first % 3 == 0) {
      candidates += kv.second;
    }
  }
  return candidates % 2 == 1;
}

string Solve(const string& s) {
  map<int, int> counts;
  int sum = 0;
  for (int i=0;i<s.size();++i) {
    int digit = c2i(s[i]);
    sum += digit;
    counts[digit]++;
  }

  for (auto& kv : counts) {
    int digit = kv.first;
    if ((sum - digit) % 3 == 0) {
      counts[digit]--;
      if (!Play(sum - digit, counts)) {
        // T lose
        return "S";
      }
      counts[digit]++;
    }
  }
  return "T";
}

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  int T;
  ss >> T;
  for (int tc=1; tc<=T; ++tc) {
    getline(cin, line);
    cout << "Case " << tc << ": " << Solve(line) << endl;
  }
}
