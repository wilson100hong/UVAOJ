#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

// word1: horizontal
// word2: vertical
bool CommonLetter(const string& word1, const string& word2, int& c1, int& c2) {
  int appear[26];
  for (int i = 0; i < 26; ++i)
     appear[i] = -1;

  int c;
  for (int i = 0; i < word2.length(); ++i) {
    c = word2[i] - 'A';
    if (appear[c] == -1)
      appear[c] = i;
  }
  for (int i = 0; i < word1.length(); ++i) {
    c = word1[i] - 'A';
    if (appear[c] != -1) {
      c1 = i; c2 = appear[c];
      return true;
    }
  }
  return false;
}

void DumpResult(string words[4], int cc[4]) {
  int len[4];
  for (int i = 0; i < 4; ++i)
    len[i] = words[i].length();
  int mid = max(cc[1], cc[3]);
  // Top part
  for (int h = 0; h < mid; h++) {
    for (int col = 0; col <= cc[0]; ++col) {
      if (col == cc[0] && h >= mid - cc[1])
        cout << words[1][h - mid + cc[1]];
      else 
        cout << " ";
    }
    if (h >= mid - cc[3]) {
      for (int col = cc[0] + 1; col <= len[0] + 3 + cc[2]; ++col) {
        if (col == len[0] + 3 + cc[2]) 
          cout << words[3][h - mid + cc[3]];
        else
          cout << " ";
      }
    }
    cout << endl;
  }

  // Mid part
  cout << words[0] << "   " << words[2] << endl;
  
  // Bottom part
  int end = max(len[1] - cc[1], len[3] - cc[3]) - 1;
  for (int h = 0; h < end; h++) {
    for (int col = 0; col <= cc[0]; ++col) {
      if (col == cc[0] && cc[1] + 1 + h < len[1])
        cout << words[1][cc[1] + 1 + h];
      else 
        cout << " ";
    }
    if (cc[3] + 1 + h < len[3]) {
      for (int col = cc[0] + 1; col <= len[0] + 3 + cc[2]; ++col) {
        if (col == len[0] + 3 + cc[2]) 
          cout << words[3][cc[3] + 1 + h];
        else
          cout << " ";
      }
    }    
    cout << endl;
  }
}

int main() {
  string line;
  string words[4];
  int cc[4];
  bool first = true;
  while(getline(cin, line)) {
    if (line == "#")
      break;

    stringstream ss(line);
    for (int i = 0; i < 4; ++i)
      ss >> words[i];
    bool ok = CommonLetter(words[0], words[1], cc[0], cc[1]) &&
              CommonLetter(words[2], words[3], cc[2], cc[3]);
    //cout << cc[0] << cc[1] << cc[2] << cc[3] << endl;
    if (first)
      first = false;
    else
      cout << endl;
    
    if (ok) 
      DumpResult(words, cc);
    else
      cout << "Unable to make two crosses" << endl;
  }
}
