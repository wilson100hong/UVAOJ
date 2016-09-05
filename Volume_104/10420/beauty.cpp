#include <iostream>
#include <map>

using namespace std;

string get_country(const string& line) {
  size_t fpos = line.find(" ");
  return line.substr(0, fpos);
}

int main() {
  string line;
  int n;
  cin >> n;
  map<string, int> beauties;
  getline(cin, line);  // eat line-break
  while(n--) {
    getline(cin, line);
    string country = get_country(line);
    if (beauties.count(country) == 0) {
      beauties[country] = 0;
    }
    beauties[country]++;
  }
  for (const auto& kv : beauties) {
    cout << kv.first << " " << kv.second << endl;
  }
}

