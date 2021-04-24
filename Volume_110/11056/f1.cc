#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>
#include <tuple>
using namespace std;

string lower(const string& s) {
  string r = s;
  for (int i=0;i<r.size();++i) {
    if ('A' <= r[i] && r[i] <= 'Z') {
      r[i] = r[i] - 'A' + 'a';
    }
  } 
  return r;
}

int main() {
  string line;
  while (getline(cin, line)) {
    int N = stoi(line);
    vector<tuple<long long, string, string>> pilots;
    string name, colon, t0, t1, t2;
    long long min, sec, ms;
    
    for (int i=0;i<N;++i) {
      getline(cin, line);
      stringstream ss(line);
      ss >> name >> colon >> min >> t0 >> sec >> t1 >> ms >> t2; 
      long long time = ms + sec * 1000 + min * 60 * 1000;
      pilots.emplace_back(time, lower(name), name);
    }

    getline(cin, line); // blank line

    sort(pilots.begin(), pilots.end());
    for (int i = 0, j=1; i < N; i+=2, j++) {
      cout << "Row " << j << endl;
      cout << get<2>(pilots[i]) << endl;
      if (i+1 < N) {
        cout << get<2>(pilots[i+1]) << endl;
      }
    }
    cout << endl;
  }
}