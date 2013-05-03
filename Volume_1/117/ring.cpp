#include <iostream>
#include <vector>
using namespace std;
int edges[26][26];
int dist[26][26];
#define MAX_INT 1<<30

void dump() {
  cout << "edges: " << endl;
  for (int i = 0; i < 26; ++i) {
    for (int j = 0; j < 26; ++j) {
      if (edges[i][j] < MAX_INT)
        cout << edges[i][j] << ", ";
      else 
        cout << "--, ";
    }
    cout << endl;
  }
}

int bellmanFord(int src, int dst) {
//  dump();
  for (int v = 0; v < 26; ++v)
    for (int i = 0; i < 26; ++i)
      for (int j = 0; j < 26; ++j) {
        if (i != j && edges[i][j] < MAX_INT 
           && dist[src][j] > dist[src][i] + edges[i][j]) {
          dist[src][j] = dist[src][i] + edges[i][j];
        }
      }
  return dist[src][dst];
}

int main() {
  string street;
  vector<string> streets;
  while (getline(cin, street)) {
    if (street == "deadend") {
      // 1. initialize edges; 
      for (int i = 0; i < 26; ++i) {
        edges[i][i] = MAX_INT;
        dist[i][i] = 0;
        for (int j = 0; j < 26; ++j) {
          if (i != j) { 
            edges[i][j] = MAX_INT;
            dist[i][j] = MAX_INT; 
          }
        }
      }
      int sum = 0;
      for (int i = 0; i < streets.size(); ++i) {
        string st = streets[i];
        int st_a = (int) st[0] - 'a';
        int st_b = (int) st[st.length()-1] - 'a';
        int len = st.length();
        edges[st_a][st_b] = len;
        edges[st_b][st_a] = len;
        sum += len;
      }

      int src = -1, dst = -1;
      // calc src and dst
      for (int i = 0; i < 26; ++i) {
        int degree = 0;
        for (int j = 0; j < 26; ++j) {
          if (i != j && edges[i][j] < MAX_INT)
            degree++;
        }
        if (degree % 2 == 1) {
          if (src == -1)
            src = i;
          else 
            dst = i;
        }
      }
      
      //cout << sum << endl;
      //cout << "src: " << src << ", dst: " << dst << endl;
      if (src != -1 && dst != -1) 
        sum += bellmanFord(src, dst);
      
      cout << sum << endl;
      // clear
      streets.clear();
    } else {
      // push to vector
      streets.push_back(street);
    }
  }
}
