#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
using namespace std;

int main() {
  string line;
  map<char, vector<char> > chambers;
  set<char> lit_chambers;
  char theseus, minotaur;
  int cnt, K;
  while (getline(cin, line)) {
    if (line == "#")
      break;
    // 1. Parse the line into chambers, theseus and minotaur
    // remember sort the edges alphabetically
    int period = line.find('.');
    string labyrinth = line.substr(0, period);
    string rest = line.substr(period + 1, line.length() - period -1);
    stringstream ss1(labyrinth);
    string token;
    while (getline(ss1, token, ';')) {
      //cout << token << endl;
      char u = token[0];
      if (chambers.find(u) == chambers.end()) {
        vector<char> vs;
        chambers[u] = vs;
      }
      for (int i = 2; i < token.length(); ++i)
        chambers[u].push_back(token[i]);
        
    }
    stringstream ss2(rest);
    ss2 >> minotaur >> theseus >> K;
    cnt = 0;
    
    // 2. Minotaur escape, theseus chase
    while (1) {
      char next_minotaur = minotaur;
      for (int i = 0; i < chambers[minotaur].size(); ++i) {
        char c = chambers[minotaur][i];
        if (c != theseus &&
            lit_chambers.find(c) == lit_chambers.end()) {
          next_minotaur = c;
          break;
        }
      }
      
      if (next_minotaur == minotaur) {
        // minotaur is trapped.
        cout << "/" << minotaur << endl;
        break;
      }

      cnt++;
      if (cnt == K) {
        lit_chambers.insert(minotaur);
        cout << minotaur << " ";
        cnt = 0;
      }
      theseus = minotaur;
      minotaur = next_minotaur;
    }

    // Clear all
    chambers.clear();
    lit_chambers.clear();
  }
  
}
