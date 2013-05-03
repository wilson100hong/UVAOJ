#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

map<char, int> charToInt;
vector<char> letters;
#define MAX_N 26

// if x < y, smaller[x][y] = true;
bool smaller[MAX_N][MAX_N];
int smaller_num[MAX_N];
bool used[MAX_N];

int N;

void rec_solve(string s) {
  if (s.length() == N) {
    cout << s << endl;
    return;
  }
  for (int i=0;i<N;++i) {
    if (used[i] == false && smaller_num[i] == 0) {
      used[i] = true;
      for (int j=0;j<N;++j) {
        if (smaller[i][j])
          smaller_num[j]--; 
      }
      
      rec_solve(s + letters[i]);

      for (int j=0;j<N;++j) {
        if (smaller[i][j])
          smaller_num[j]++; 
      }
      used[i] = false;
    }
  }
}


int main() {
  string line;
  int first = true;
  while(getline(cin, line)) {
    // 0. init
    charToInt.clear();
    letters.clear();
    for (int i=0;i<MAX_N;++i) {
      smaller_num[i] = 0;
      used[i] = false;
      for (int j=0;j<MAX_N;++j)
        smaller[i][j] = false;
    }

    // 1. read in all chars 
    stringstream s1(line);
    char c;
    while(s1 >> c) {
      letters.push_back(c);           
    }
    sort(letters.begin(), letters.end());
    N = letters.size();
    for(int i=0;i<N;++i)
      charToInt[letters[i]] = i;
    
    // 2. read all rules
    getline(cin, line);
    stringstream s2(line);
    
    char c1, c2;
    while (s2 >> c1 >> c2) {
      int x = charToInt[c1];
      int y = charToInt[c2];
      smaller[x][y] = true;
      smaller_num[y]++;
    }
    //for (int i=0;i<N;++i)
     // cout << letters[i] << smaller_num[i] << endl;
      // 3. do job
    if (first) 
      first = false;
    else
      cout << endl;
    rec_solve("");
  }
  return 0;
}
