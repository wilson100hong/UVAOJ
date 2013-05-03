#include <algorithm>
#include <vector>
#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define WORST 1<<30

map<char, int> bins;
map<char, int> trashes;
int trash2Int(char c) {
  // P, G, A, S, N
  return trashes[c];
}


int bin2Int(char c) {
  // r, o, y, g, b
  return bins[c]; 
}

// Bin order: r, o, y, g, b
struct Policy{
  int bin[5];
};

void dump(const Policy& po) {
  for (int i=0;i<5;++i) 
    cout << po.bin[i] << ",";
  cout << endl;
}

int diff(const Policy& p1, const Policy& p2) {
  int bin2[5];
  for (int i=0;i<5;++i) 
    bin2[i] = p2.bin[i];
  int sum = 0;
  for (int i=0;i<5;++i) {
    if (p1.bin[i] != bin2[i]) {
      sum++;
      /*for (int j=4;j>i;--j) {
        if (bin2[j] == p1.bin[i]) {
          bin2[j] = bin2[i];
          bin2[i] = p1.bin[i];
          sum++;
          break;
        }
      }*/
    }
  }
  return sum;
}

int main() {
  bins['r'] = 0;
  bins['o'] = 1;
  bins['y'] = 2;
  bins['g'] = 3;
  bins['b'] = 4;
  trashes['P'] = 0;
  trashes['G'] = 1;
  trashes['A'] = 2;
  trashes['S'] = 3;
  trashes['N'] = 4;

  vector<Policy> policies;
  string line;
  int best_index = 0;

  while (getline(cin, line)) {
    if (line[0] == '#')
      break;
    else if (line[0] == 'e') {
      int index = -1;
      int best = WORST;
      for (int i=0; i<policies.size(); ++i) {
        int sum = 0;
        for (int j=0; j<policies.size(); ++j) {
          if (j!=i) {
            sum += diff(policies[i], policies[j]);
          }
        }
        if (best > sum) {
          best = sum;
          index = i; 
        }
      }
      cout << index + 1 << endl;
      policies.clear();
    } else {
      Policy po;
      int cursor = 0;
      int bin, trash;
      while (cursor < line.length()) {
        bin = line[cursor];
        cursor += 2;
        trash = line[cursor];
        cursor += 2;
        po.bin[bin2Int(bin)] = trash2Int(trash);
      }
      // TEST: dump
      //dump(po);
      policies.push_back(po);
    }
  }
}
