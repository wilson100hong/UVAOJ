#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;


vector<string> eatline() {
  string line;
  getline(cin, line);

  vector<string> tokens;
  stringstream ss(line);
  string s;
  while (getline(ss, s, ' ')) {
    tokens.push_back(s);
  }
  return tokens;
}

int main() {
  vector<string> tokens;

  while (1) {
    double tank = 0;
    double max_usage = 0.0;
    double usage = 0.0;
    int leaks = 0;

    // litres per 0.01 km

    tokens = eatline();
    long pos = stoi(tokens[0]);

    // per 100 km
    long consumption = stoi(tokens[3]);
    
    if (consumption == 0.0) break;

    while (1) {
      tokens = eatline();

      long e_pos = stoi(tokens[0]);
      long dist = (e_pos - pos) * (consumption + leaks*100.0);

      usage += dist;
      max_usage = max(max_usage, usage);

      pos = e_pos;

      if (tokens[1] == "Goal") {
        cout << fixed;
        cout << setprecision(3) << (max_usage/100.0) << endl;
        break;
      } else if (tokens[1] == "Leak") {
        leaks ++;
      } else if (tokens[1] == "Mechanic") {
        leaks = 0;
      } else if (tokens[1] == "Gas") {
        usage = 0;
      } else if (tokens[1] == "Fuel") {
        consumption = stoi(tokens[3]);
      } else {
        cout << "YOU FOOL" << endl;
      }
    }
  }
}
