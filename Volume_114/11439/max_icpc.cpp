#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

#define NO_MATCH -1
#define NO_PARENT -1
#define NO_CROSS -1

bool AllMatch(const vector<int>& matched) {
  for (int i = 0; i < matched.size(); ++i) {
    if (matched[i] == NO_MATCH) {
      return false;
    }
  }
  return true;
}

// General Matcher that applied Edmond Algorithm.
// wiki: http://en.wikipedia.org/wiki/Edmonds'_algorithm
// refer: http://www.csie.ntnu.edu.tw/~u91029/Matching.html
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
    // Greedy match first
    Greedy();
    // Edmond to find augmented path
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
    if (x == blossom_[x])
      return x;
    blossom_[x] = GetBlossom(blossom_[x]);
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
    int z = i, b = j;
    if (color_[i] == BLUE) {
      swap(z, b);
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
      int u = worklist.front();  worklist.pop();
      for (int v = 0; v < size_; ++v) {
        if (!HasEdge(u, v)) continue;
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
  
  vector<vector<int> > graph_;
  int size_;
  vector<int> matches_;
  int threshold_;
};

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
    
    // Binary Search
    EdmondMatcher matcher(graph);
    vector<int> matched;
    int L = 0, H = sorted_scores.size() - 1;
    while (L < H) {
      int MID = (L + 1 + H) / 2;  // round up
      matched = matcher.Match(sorted_scores[MID]);
      if (AllMatch(matched)) {
        L = MID;
      } else {
        H = MID - 1;
      }
    }
    int best = sorted_scores[L];
    cout << "Case " << t << ": " << best << endl;
  }
}
