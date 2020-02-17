#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

string Solve(const vector<string>& rows) {
  int len = rows[0].size() - 2;
  vector<char> res(len, 0);

  for (int r=1;r<rows.size()-1;++r) {
    const string& line = rows[r];
    int power = r-1;  // 2 ^ base
    for (int j=1;j<line.size()-1;++j) {
      if (line[j] == '\\') {
        res[j-1] += (1 << power);
      }
    }
  }

  return string(res.begin(), res.end());
}

int main() {
  int N;
  cin >> N;
  string line;
  getline(cin, line);  // need to getline after cin.

  bool first_case = true;
  while (N--) {
    // Read 10 rows
    vector<string> rows;
    if (!first_case) {
      getline(cin, line);
    }
    first_case = false;
    for (int i=0;i<10;++i) {
      getline(cin, line);
      rows.push_back(line);
    }
    cout << Solve(rows) << endl;
  }
}
