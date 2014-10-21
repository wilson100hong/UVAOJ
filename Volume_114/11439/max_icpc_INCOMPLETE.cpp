#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define NO_MATCH -1
#define NO_PARENT -1
#define NO_CROSS -1

// ---- Edmond start ----
class EdmondMatcher{
public:
  enum Color { NO_COLOR, RED, BLUE };
  enum State { IMPOSSIBLE, NO_VISIT, EVEN, ODD};

  EdmondMatcher(const vector<vector<int> >& graph)
    : graph_(graph) {
    size_ = graph_.size();
    threshold_ = 0;
  }

  vector<int> Match(int threshold) {
    threshold_ = threshold;
    matches_.assign(size_, NO_MATCH);

    // Greedy match first, then Edmond
    cout << "Greedy start" << endl;
    Greedy();

    cout << "Edmond start" << endl;
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
  bool HasEdge(int u, int v) {
    return u != v && (graph_[u][v] >= threshold_);
  }

  void Greedy() {
    for (int u = 0; u < size_; ++u) {
      for (int v = 0; v < size_; ++v) {
        if (HasEdge(u, v) &&
            matches_[u] == NO_MATCH &&
            matches_[v] == NO_MATCH) {
          matches_[u] = v;
          matches_[v] = u;
        }
      }
    }
  }

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
    // TODO: here has inf loop
    cout << "    GetBlossom, x= " << x << endl;
    if (x == blossom_[x]) return x;
    blossom_[x] = GetBlossom(blossom_[x]);
    cout << "    GetBlossom, blossom_[x]= " << blossom_[x] << endl;
    return blossom_[x];
  }

  int LCA(int root, int x, int y) {
    int i = GetBlossom(x);
    int j = GetBlossom(y); 

    while(i != j && color_[i] != BLUE && color_[j] != RED) {
      cout << "    inf loop... " << endl;
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
    cout << "BFS start" << endl;
    state_[root] = EVEN;
    parent_[root] = root;

    queue<int> worklist;
    worklist.push(root);

    while (!worklist.empty()) {
      int u = worklist.front();  worklist.pop();
      cout << "traverse from u = " << u << endl;
      for (int v = 0; v < size_; ++v) {
        if (!HasEdge(u, v)) continue;
        if (GetBlossom(u) == GetBlossom(v)) continue;

        cout << " v=" << v << endl;
        switch(state_[v]) {
          case NO_VISIT: {
            cout << "  NO_VISIT " << endl;
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
            cout << "  EVEN " << endl;
            int b = LCA(root, u, v);
            cout << "  LCA: " << b << endl;
            Contract(b, u, v, worklist);
            Contract(b, v, u, worklist);
            cout << "  contracted done" << endl;
          }
          break;
          case ODD:
          case IMPOSSIBLE:
          default:
            cout << "  NEVERMIND " << endl;
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
  
  vector<vector<int> > graph_;
  int size_;
  vector<int> matches_;
  int threshold_;
};
// ---- Edmond end ----

void DumpVector(const vector<int>& vec) {
  for (int i = 0; i < vec.size(); ++i) {
    cout << vec[i] << " ";
  }
  cout << endl;
}

void DumpGraph(const vector<vector<int> >& graph) {
  for (int i = 0; i < graph.size(); ++i) {
    DumpVector(graph[i]);
  }
}

bool AllMatch(const vector<int>& matched) {
  for (int i = 0; i < matched.size(); ++i) {
    if (matched[i] == NO_MATCH) {
      return false;
    }
  }
  return true;
}

struct score_compare {
  bool operator() (const int& a, const int& b) const {
    return a < b;
  }
};

int main () {
  int T;  cin >> T;
  vector<vector<int> > graph;
  for (int t = 1; t <= T; t++) {
    // Get Input
    int W;  cin >> W;
    int N = 1 << W;

    graph.clear();
    for (int n = 0; n < N; ++n) {
      vector<int> edges; 
      graph.push_back(edges);
    }
    set<int, score_compare> scores;
    for (int n = 0; n < N; ++n) {
      graph[n].push_back(-1);  // self
      for (int m = n + 1; m < N; ++m) {
        int M;  cin >> M;
        scores.insert(M);
        graph[n].push_back(M);
        graph[m].push_back(M);
      }
    }
    // construct sorted scores
    vector<int> sorted_scores;
    for (set<int, score_compare>::iterator it = scores.begin();
        it != scores.end(); ++it) {
      sorted_scores.push_back(*it);
    }
    //cout << endl;
    DumpVector(sorted_scores);
    //DumpGraph(graph);
    
    // Binary Search
    EdmondMatcher matcher(graph);
    vector<int> matched;
    int L = 0, H = sorted_scores.size() - 1;
    while (L < H) {
      int MID = (L + 1 + H) / 2;  // round up
      cout << "threshold: " << sorted_scores[MID] << endl;
      matched = matcher.Match(sorted_scores[MID]);
      if (AllMatch(matched)) {
        L = MID;
      } else {
        H = MID - 1;
      }
    }
    cout << L << endl;
    int best = sorted_scores[L];
    DumpVector(matcher.Match(best));
    cout << "Case " << t << ": " << best << endl;
    
  }
}
