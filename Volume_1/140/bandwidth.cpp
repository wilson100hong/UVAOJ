#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

#define N_MAX 8

bool edges[N_MAX][N_MAX];
bool used[N_MAX];
map<char, int> charToInt;
vector<char> letters;

string best_order;
int min_bw;

int bandwidth(const vector<int>& sequence) {
  map<int, int> pos;
  int n = sequence.size();
  for (int i=0;i<n;++i)
    pos[sequence[i]] = i;

  int max = 0;
  for (int i=0;i<n;++i) {
    for(int j=0;j<n;++j) {
      if (edges[i][j]) {
        int bw = abs(pos[i] - pos[j]);
        if (bw > max) 
          max = bw;
      }
    }
  }
  return max;
}

// TODO: optimize
string gen_order(const vector<int>& seq) {
  string s = "";
  for (int i=0;i<seq.size();++i)
    s = s + letters[seq[i]] + " ";
  return s;
}

void rec(vector<int> seq) {
  if (seq.size() == letters.size())  {
    int bw = bandwidth(seq);
    if (bw < min_bw) {
      min_bw = bw;
      best_order =  gen_order(seq);
    }
    return;
  }
  for(int i=0;i<letters.size();++i) {
    if (!used[i]) {
      used[i] = true;
      seq.push_back(i);
      
      rec(seq);
      
      seq.pop_back();
      used[i] = false;
    }
  }
}

int main () {
  string line;
  while (getline(cin, line)) {
    if (line == "#")
      break;
    charToInt.clear();
    letters.clear();
    for (int i=0;i<N_MAX;++i) {
      used[i] = false;
      for (int j=0;j<N_MAX;++j)
        edges[i][j] = 0;
    }
    
    // 0. build map and vector
    for (int i=0;i<line.length();++i) {
      char c = line[i];
      if (c != ':' && c != ';' &&  
          charToInt.find(c) == charToInt.end()) {
        letters.push_back(c);
        charToInt[c] = 1;
      }
    }
    sort(letters.begin(), letters.end());
    for (int i=0;i<letters.size();++i) 
       charToInt[letters[i]] = i;
    //for (int i=0;i<letters.size();++i)
     // cout << letters[i] << endl;

    // 1. build edges
    int src = -1;
    for (int i=0;i<line.length();++i) {
      char c = line[i];
      if (c == ';')
        src = -1;
      else if (src == -1) 
        src = charToInt[c];
      else if (c == ':') 
        ;
      else {
        int dst = charToInt[c];
        edges[src][dst] = true;
        edges[dst][src] = true;
      }
    }
    // TEST edges
    /*
    for (int i=0;i<letters.size();++i) {
      for (int j=0;j<letters.size();++j) 
        cout << edges[i][j] << ",";
      cout << endl;
    }*/

    // 2. produce all permutation
    best_order = "";
    min_bw = 1 << 30;
    vector<int> vec;
    rec(vec);
    cout << best_order << "-> " << min_bw << endl;
  }
}
