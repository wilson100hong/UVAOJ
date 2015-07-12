#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool is_number(string& s) {
  return  s.size() > 0 && s[0] <= '9' && s[0] >= '0';
}

int stoi(string& s) {
  int result = 0;
  for (int i = s.size() - 1; i >= 0; --i) {
    result = result * 10 + (s[i] - '0');
  }
  return result;
}

string reverse(string& s) {
  string result = "";
  for (int i = s.size() -1; i >= 0; --i) {
    result += s[i];
  }
  return result;
}

int abs(int n) {
  return n > 0 ? n : -n;
}

struct word {
  string str;
  // start row & col
  int sr;
  int sc; 
  // delta row & col
  int dr;
  int dc;
};

int main() {
  int n;
  cin >> n;
  while (1) {
    if (n == 0) break;
    vector<string> matrix;
    for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      matrix.push_back(s);
    }

    // build dict from matrix
    vector<word> dict;
    // 1. row
    for (int r = 0; r < n; ++r) {
      dict.push_back({matrix[r], r, 0, 0, 1});
      dict.push_back({reverse(matrix[r]), r, n - 1, 0, -1});
    }
    // 2. col
    for (int c = 0; c < n; ++c) {
      string str = "";
      for (int r = 0; r < n; ++r) {
        str += matrix[r][c];
      }
      dict.push_back({str, 0, c, 1, 0});
      dict.push_back({reverse(str), n - 1, c, -1, 0});
    }

    // 3. diagonal: top-left -> bottom-right
    for (int i = -n + 1; i <= n - 1; ++i) {
      string str = "";
      int r = i >= 0 ? 0 : -i; 
      int c = i >= 0 ? i : 0;
      int len = n - abs(i);
      for (int j = 0; j < len; ++j) {
        str += matrix[r + j][c + j];
      }
      dict.push_back({str, r, c, 1, 1}); 
      dict.push_back({reverse(str), r + len - 1, c + len - 1, -1, -1}); 
    }

    // 4. diagonal: top-right -> bottom-left
    for (int i = 0; i < 2 * n - 1; ++i) {
      string str = "";
      // TODO: calc r & c
      int r = i < n ? 0 : i - n + 1; 
      int c = i < n ? i : n - 1;
      int len = i < n ? i + 1 : 2 * n - 1 - i;
      for (int j = 0; j < len; ++j) {
        str += matrix[r + j][c - j];
      }
      dict.push_back({str, r, c, 1, -1}); 
      dict.push_back({reverse(str), r + len - 1, c - len + 1, -1, 1}); 
    }

    while (1) {
      string q;
      cin >> q;
      if (is_number(q)) {
        n = stoi(q);
        break;
      }
      bool ok = false;
      for (word& w : dict) {
        size_t found = w.str.find(q);
        if (found != string::npos) {
          // query
          int row = w.sr + found * w.dr;
          int col = w.sc + found * w.dc;
          cout << row + 1 << "," << col + 1 << " ";
          row += w.dr * (q.size() - 1);
          col += w.dc * (q.size() - 1);
          cout << row + 1 << "," << col + 1 << endl;
          ok = true;
          break;
        }
      }
      if (!ok) {
        cout << "Not found" << endl;
      }
    }
  }
}
