#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <algorithm>

using namespace std;
#define N_MAX 100

struct Vertex{
  vector<int> edges;
  int color; // 0: uncolor, 1: white, 2: black
  bool visit;
};

vector<Vertex> vertice;


int gmax;
vector<int> gblacks;

bool CanBeBlack(int index) {
  Vertex v = vertice[index];
  for (int i=0;i<v.edges.size();++i) {
    int ui = v.edges[i];
    if (ui < index && vertice[ui].color == 2)
      return false;
  }
  return true;
}

void Rec(int index, int num_black) {
  int n = vertice.size();
  if (index == n && gmax < num_black) {
    gmax = num_black;
    gblacks.clear();
    for (int i=0;i<n;++i) {
      if (vertice[i].color == 2) 
        gblacks.push_back(i+1);
    }
    return;
  }
  int color = vertice[index].color;
  
  if (color == 2) {
    cout << "IMPOSSIBLE" << endl;
    exit(0);
  }
 
  // 1. Let the node be WHITE
  vertice[index].color = 1;
  if (num_black + n - index - 1 > gmax) {
    Rec(index + 1, num_black);
  }
  
  // 2. the node can be BLACK
  if (CanBeBlack(index) && 
    num_black + n - index > gmax)  {
    vertice[index].color = 2;
    num_black++;
    Rec(index + 1, num_black);
  }
  
  // 3. remember restore
  vertice[index].color = color;
}

int main() {
  int m, n, k;
  cin >> m;
  while (m-- > 0) {
    vertice.clear();
    cin >> n >> k;
    for (int i=0;i<n;++i) {
      Vertex v;
      v.color = 0;
      v.visit = false;
      vertice.push_back(v);
    }
    for (int i=0;i<k;++i) {
      int src, dst;
      cin >> src >> dst;
      src--;
      dst--;
      vertice[src].edges.push_back(dst);
      vertice[dst].edges.push_back(src);
    }
    
    // TODO: all possibilities
    gmax = 0;
    gblacks.clear();
    Rec(0, 0);
    cout << gmax << endl;    
    // dump result
    bool first = true;
    for (int i=0;i<gblacks.size();++i) {
      if (first)
        first = false;
      else 
        cout << " ";
      cout << gblacks[i];
    }
    cout << endl;
  }
}
