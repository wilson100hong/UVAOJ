#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector< vector<int> > piles;
int* loc;

void dump() {
  int n = piles.size();
  for (int i=0;i<n;++i) {
    cout << i << ":";
    for (int j=0;j<piles[i].size();++j) {
       cout << " " << piles[i][j];
    }
    cout << endl;
  }
}

void resetBlocksOnTopOf(int box) {
  vector<int>& pile = piles[loc[box]];
  while (pile.back() != box) {
    int b =  pile.back();
    pile.pop_back();
    piles[b].push_back(b);
    loc[b] = b;
  }
}


void pileOver(int srcBox, int dstBox) {
  vector<int>& srcPile = piles[loc[srcBox]];
  vector<int>& dstPile = piles[loc[dstBox]];
  vector<int> tmpPile;
  while (srcPile.back() != srcBox) {
    int b = srcPile.back();
    tmpPile.push_back(b);
    srcPile.pop_back();
  }
  
  srcPile.pop_back(); // for srcBox;
  loc[srcBox] = loc[dstBox];
  dstPile.push_back(srcBox);
  
  for (int i=0;i<tmpPile.size();++i) {
    dstPile.push_back(tmpPile[i]);
    loc[tmpPile[i]] = loc[dstBox];
  }
}


int main() {
  int n, i, j;
  cin >> n;
  piles.resize(n);
  loc = new int[n];
  for(int i = 0; i < n; ++i) {
    loc[i] = i;
    piles[i].push_back(i);
  }
  string action, type;
  int a, b;
  int act = 0;
  while (cin >> action) {
    if (action == "quit") {
      break;  
    } 
    cin >> a >> type >> b;
    if (loc[a] == loc[b]) {
    } else if (action == "move" && type == "onto") {
      resetBlocksOnTopOf(a);
      resetBlocksOnTopOf(b);
      pileOver(a, b);
    } else if (action == "pile" && type == "onto") {
      resetBlocksOnTopOf(b);
      pileOver(a, b);
    } else if (action == "move" && type == "over") {
        if (loc[a] != loc[b]) {
        resetBlocksOnTopOf(a);
        pileOver(a, b);
        }
    } else if (action == "pile" && type == "over") {
         pileOver(a, b);
    }
    //cout << "--- act " << act++ << " ---" << endl; 
    //dump();
  }
  dump();
  return 0;
}
