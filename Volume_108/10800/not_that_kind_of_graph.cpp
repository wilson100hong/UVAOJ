#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

// Char to symbol
char c2s(char c) {
  if (c == 'R') {
    return '/';
  } else if (c == 'F') {
    return '\\';
  } else {  // c == 'C'
    return '_';
  }
}

void Solve(const string& str) {
  map<int, set<int>> y_x_map;
  vector<char> symbols;

  int y, min_y, max_y;
  y = min_y = max_y = 0;

  char prev_symbol = c2s(str[0]);
  y_x_map[y].insert(0);
  symbols.push_back(prev_symbol);

  for (int i=1;i<str.size();++i) {
    char symbol = c2s(str[i]);

    // Update y
    if (symbol == '/') {
      if (prev_symbol == '/') {
        y++;
      }
    } else if (symbol == '\\') {
      if (prev_symbol == '_' || prev_symbol == '\\') {
        y--;
      }
    } else {  // '_'
      if (prev_symbol == '/') {
        y++;
      }
    }

    min_y = min(min_y, y);
    max_y = max(max_y, y);
    y_x_map[y].insert(i);

    symbols.push_back(symbol);
    prev_symbol = symbol;
  }

  int height = max_y - min_y + 1;

  // Print height rows
  for (int r=0;r<height;++r) {
    int y = max_y - r;
    // Print y-axis
    cout << "|";

    auto& xs = y_x_map[y];
    int cur = 0;  // current x
    bool first = true;;
    for (int x : xs) {
      if (first) {
        cout << " ";  // Space between y-axis and graph, if any
        first = false;
      }
      while (cur < x) {
        cout << " ";
        cur++;
      }
      cout << symbols[x];
      cur++;
    }
    cout << endl;
  }

  // Print x-axis
  cout << "+-";
  for (int i=0;i<str.size();++i) {
    cout << "-";
  }
  cout << "-" << endl;
}

int main() {
  string line;
  int N;
  cin >> N;
  getline(cin, line);  // Handle cin for the line with N;
  for (int i=0;i<N;++i) {
    cout << "Case #" << i+1 << ":" << endl;
    getline(cin, line);
    Solve(line);
    cout << endl;
  }
}
