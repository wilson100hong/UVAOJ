#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

#define NO_MATCH -1
#define NO_PARENT -1
#define NO_CROSS -1

class EdmondMatcher{
public:
  enum Color { NO_COLOR, RED, BLUE };
  enum State { IMPOSSIBLE, NO_VISIT, EVEN, ODD};

  EdmondMatcher(const vector<vector<int> >& edges)
    : edges_(edges) {
    size_ = edges_.size();
  }

  vector<int> Match() {
    matches_.assign(size_, NO_MATCH);
    for (int i = 0; i < size_; ++i) {
      if (matches_[i] == NO_MATCH) {
        ClearLocals();
        if (!BFS(i)) {
          state_[i] = IMPOSSIBLE;
        }
      }
    }
    return matches_;
  }

private:
  void ClearLocals() {
    state_.assign(size_, NO_VISIT);
    parent_.assign(size_, NO_PARENT);
    blossom_.clear();
    for (int i = 0; i < size_; ++i) {
      blossom_.push_back(i);
    }
    color_.assign(size_, NO_COLOR);
    cross_1.assign(size_, NO_CROSS);
    cross_2.assign(size_, NO_CROSS);
  }


  int GetBlossom(int x) {
    if (x != blossom_[x])
      blossom_[x] = GetBlossom(parent_[x]);
    return blossom_[x];
  }

  int LCA(int root, int x, int y) {
    int i = GetBlossom(x);
    int j = GetBlossom(y); 

    while(i != j && color_[i] != BLUE && color_[j] != RED) {
      color_[i] = RED;
      color_[j] = BLUE;
      if (i != root)
        i = GetBlossom(parent_[i]);
      if (j != root)
        j = GetBlossom(parent_[j]);
    }

    int z, b;
    if (color_[i] == RED) {
      z = i;
      b = j;
    } else {
      z = j;
      b = i;
    }

    for (i = b; i != z; i = GetBlossom(parent_[i])) {
      color_[i] = NO_COLOR;
    }
    color_[z] = NO_COLOR;

    return b;
  }
  
  void Contract(int b, int x, int y, queue<int>& worklist) {
    for (int i = GetBlossom(x); i != b; i = GetBlossom(parent_[i])) {
      blossom_[i] = b;
      if (state_[i] == ODD) {
        cross_1[i] = x;
        cross_2[i] = y;
        worklist.push(i);
      }
    }
  }

  void Relax(int root, int x) {
    if (root == x) return;
    if (state_[x] == EVEN) {
      int p = parent_[x];
      int g = parent_[p];
      Relax(root, g);
      matches_[p] = g;
      matches_[g] = p; 
    } else if (state_[x] == ODD) {
      Relax(matches_[x], cross_1[x]);
      Relax(root, cross_2[x]);
      matches_[cross_2[x]] = cross_1[x];
      matches_[cross_1[x]] = cross_2[x];
    }
  }

  bool BFS(int root) {
    state_[root] = EVEN;
    parent_[root] = root;

    queue<int> worklist;
    worklist.push(root);

    while (!worklist.empty()) {
      int u = worklist.front();
      worklist.pop();
      for (int i = 0; i < edges_[u].size(); ++i) {
        int v = edges_[u][i];
        if (GetBlossom(u) == GetBlossom(v)) continue;

        switch(state_[v]) {
          case NO_VISIT: {
            if (matches_[v] == NO_MATCH) {
              Relax(root, u);
              matches_[u] = v;
              matches_[v] = u;
              return true;
            } else {
              state_[v] = ODD;
              parent_[v] = u;
              int w = matches_[v];
              state_[w] = EVEN;
              parent_[w] = v;
              worklist.push(w);
            }
          }
          break;

          case EVEN: {
            int b = LCA(root, u, v);
            Contract(b, u, v, worklist);
            Contract(b, v, u, worklist);
          }
          break;
          case ODD:
          case IMPOSSIBLE:
          default:
          break;
        }
      }
    }
    return false;
  }

  vector<int> state_;
  vector<int> parent_;

  vector<int> blossom_;
  vector<int> color_;
  vector<int> cross_1;
  vector<int> cross_2;
  
  vector<vector<int> > edges_;
  int size_;
  vector<int> matches_;
};


vector<int> MakeVec(int array[], int cnt) {
  return vector<int>(array, array + cnt);
}

void DumpVec(const string& str, const vector<int>& vec) {
  cout << str << ": " << endl;
  for (int i = 0; i < vec.size(); ++i) {
    cout << vec[i] << " ";
  }
  cout << endl;
}

void InitGraph(vector<vector<int> >& graph) {
  int n0[] = {2, 4};
  int n1[] = {2, 3};
  int n2[] = {0, 1};
  int n3[] = {1, 6, 7};
  int n4[] = {5, 0};
  int n5[] = {4, 6};
  int n6[] = {3, 5};
  int n7[] = {3, 8};
  int n8[] = {7, 9};
  int n9[] = {8};
  graph.push_back(MakeVec(n0, 2));
  graph.push_back(MakeVec(n1, 2));
  graph.push_back(MakeVec(n2, 2));
  graph.push_back(MakeVec(n3, 3));
  graph.push_back(MakeVec(n4, 2));

  graph.push_back(MakeVec(n5, 2));
  graph.push_back(MakeVec(n6, 2));
  graph.push_back(MakeVec(n7, 2));
  graph.push_back(MakeVec(n8, 2));
  graph.push_back(MakeVec(n9, 1));
}

// Test
int main() {
  vector<vector<int> > graph;
  InitGraph(graph);
 
  EdmondMatcher matcher(graph);
  vector<int> matches = matcher.Match();

  DumpVec("result", matches);
}
