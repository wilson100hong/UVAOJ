#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  int rounds;
  cin >> rounds;
  vector<string> land_strs;
  vector<string> queries;

  string line;
  getline(cin, line); 
  getline(cin, line); 
  while (rounds-- > 0) {
    land_strs.clear();
    queries.clear();
    while(getline(cin, line) && !line.empty()) {
      if (line[0] =='W' || line[0] == 'L') {
        land_strs.push_back(line);
      } else {
        queries.push_back(line);
      }
    }

    for (int i = 0; i < land_strs.size(); ++i)
      cout << "land: " << land_strs[i] << endl;
    cout << endl;
    for (int i = 0; i < queries.size(); ++i)
      cout << "queries: " << queries[i] << endl;
  }
}
