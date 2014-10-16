#include <iostream>
#include <map>
#include <vector>
#include <queue>

using namespace std;

#define NO_MATCH -1
#define NO_PARENT -1
#define NO_CROSS -1

#define IMPOSSIBLE -2  // visited, impossible node for aug-path
#define NO_VISIT -1  // not visited
#define EVEN 0   // visited, even node
#define ODD 1    // visited, odd node

#define NO_COLOR -1
#define RED 1
#define BLUE 2

#define DEBUG

vector<int> MakeVec(int array[], int cnt) {
  return vector<int>(array, array + cnt);
}

void DumpGraph(const vector<vector<int> >& graph) {
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j) 
      cout << graph[i][j] << ",";
    cout << endl;
  }
}

void DumpVec(const string& str, const vector<int>& vec) {
  cout << str << ": " << endl;
  for (int i = 0; i < vec.size(); ++i) {
    cout << vec[i] << ", ";
  }
  cout << endl;
}

class EdmondMatcher{
public:
  EdmondMatcher(const vector<vector<int> >& edges)
    : edges_(edges) {
    size_ = edges_.size();
  }

  bool BFS(int root);
  void AlterPath(int root, int x);
  int LCA(int root, int x, int y);
  void Contract(int b, int x, int y);

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

  void ClearLocals() {
    state_.assign(size_, NO_VISIT);
    parent_.assign(size_, NO_PARENT);
    blossom_.clear();
    for (int i = 0; i < size_; ++i) {
      blossom_.push_back(i);
    }
    color.assign(size_, NO_COLOR);
    cross_1.assign(size_, NO_CROSS);
    cross_2.assign(size_, NO_CROSS);
  }

  // Return the the root of blossom x belongs. Return x itself if
  // not in any blossom.
  // Also recursively update x's ancestor upto to blossom root.
  int GetBlossom(int x) {
    if (x != blossom_[x])
      blossom_[x] = GetBlossom(parent_[x]);
    return blossom_[x];
  }

  //void Union(int b, int x) {
    //blossom_[x] = b;
  //}

  void Dump() {
    DumpVec("state", state_);
    DumpVec("matches", matches_);
    DumpVec("parent", parent_);
    DumpVec("blossom", blossom_);
    DumpVec("color", color);
    DumpVec("cross_1", cross_1);
    DumpVec("cross_2", cross_2);
  }

  // Local variables in BFS
  //queue<int> worklist;
  
  vector<int> state_;   // NO_VISIT, EVEN, ODD or IMPOSSIBLE
  vector<int> parent_;  // node's immediate parent node

  // nodes in same blossom has value equals to blossom root.
  vector<int> blossom_;
  vector<int> color;
  vector<int> cross_1;
  vector<int> cross_2;
  
  // Global variables 
  vector<vector<int> > edges_;
  int size_;
  vector<int> matches_;
};

// TODO: comment
void EdmondMatcher::AlterPath(int root, int x) {
  cout << "AlterPath: " << root << ", " << x << endl;
  if (root == x) return;
  // -: unmatch
  // =: match
  //    r.......g-p=x
  // => r.......g=p-x
  // but we don't need to handle x
  if (state_[x] == EVEN) {
    //cout << "EVEN:" << endl;
    int p = parent_[x];
    int g = parent_[p];
    AlterPath(root, g);
    matches[p] = g;
    matches[g] = p; 
  } else if (state_[x] == ODD) {
    //cout << "ODD:" << endl;
    AlterPath(cross_1[x], matches[x]);
    AlterPath(root, cross_2[x]);
    matches[cross_2[x]] = cross_1[x];
    matches[cross_1[x]] = cross_2[x];
  } else {
    cout << "IMPOSSIBLE: " << state_[x];
  }
}

// Find the Least Common Ancestor of node x and y, given root.
int EdmondMatcher::LCA(int root, int x, int y) {
#ifdef DEBUG
  cout << "LCA for: {" << x << "," << y << "}, root" << root << endl;
#endif

  // x and y in different blossom.
  int i = GetBlossom(x);  // root ... x is RED
  int j = GetBlossom(y);  // root(not include) ... y is BLUE

  // color nodes iterativaly on their blossoms until:
  // 1. node collision: i == j
  // 2. node meet different color node, which is the path of the other path:
  //    a. color[i] is BLUE
  //    b. color[j] is RED
  while(i != j && color[i] != BLUE && color[j] != RED) {
    color[i] = RED;
    color[j] = BLUE;
    if (i != root)
      i = GetBlossom(parent_[i]);
    if (j != root)
      j = GetBlossom(parent_[j]);
  }

  //           ----x
  //  r---i--j/
  //          \--y    => color[i] is RED: z = i, b = j
  // 
  //           --x
  //  r---j--i/
  //          \----y  => color[i] is BLUE: z = j, b = i
  int z, b;
  if (color[i] == RED) {
    z = i;
    b = j;
  } else {  // color[i] == BLUE
    z = j;
    b = i;
  }

  // TODO: clean color from z->b, including b
  for (i = b; i != z; i = GetBlossom(parent_[i])) {
    color[i] = NO_COLOR;
  }
  color[z] = NO_COLOR;

  // we don't need to clear b->x and b->y, because GetBlossom(x) and GetBlossom(y)
  // should return b and skip all colored nodes. This is smart!
  return b;
}


void EdmondMatcher::Contract(int b, int x, int y, queue<int>& worklist) {
  for (int i = GetBlossom(x); i != b; i = GetBlossom(parent_[i])) {
    // here i is either a not-contracted node or root of the blossom
    //Union(b, i);
    blossom_[i] = b;
    // An ODD node n is only handled once here: when it is contracted the first time.
    // It will never be considered later.
    // 1. GetBlossom(n) never return the n. It will return the blossom root instead
    // 2. BFS never push n into worklist.
    if (state_[i] == ODD) {
      //    --i----x      c1[i] = x
      //  b/   
      //   \--y        => c2[i] = y
      cross_1[i] = x;
      cross_2[i] = y;
      worklist.push(i);
    }
  }
}

// Return true if there is augmented path from root.
bool EdmondMatcher::BFS(int root) {
  state_[root] = EVEN;  // root is always EVEN 
  parent_[root] = root;  // and itself parent

  queue<int> worklist;
  worklist.push(root);

  while (!worklist.empty()) {
    int u = worklist.front();
    worklist.pop();
    for (int i = 0; i < edges_[u].size(); ++i) {
      int v = edges_[u][i];
      // If u and v are in the same blossom, skip v
      // because v has been processed before.
      if (GetBlossom(u) == GetBlossom(v)) continue;

      // u and v are in different blossom.
      switch(state_[v]) {
        case NO_VISIT: {
          if (matches[v] == NO_MATCH) { // EVEN, aug path found
            cout << "root: " << root << endl;
            cout << "path_u: " << u << " _v:" << v << endl;
            Dump();
            AlterPath(root, u);
            matches[u] = v;
            matches[v] = u;
            return true;
          } else {  // ODD
            state_[v] = ODD;
            parent_[v] = u;
            int w = matches[v];
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
        case ODD:  // skip
        case IMPOSSIBLE:   // skip
        default:
        break;
      }
    }
  }
  return false;
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
  //DumpGraph(graph);
 
  EdmondMatcher matcher(graph);
  cout << "start match:" << endl;
  vector<int> matches = matcher.Match();

  //cout << "match result:" << endl;
  //for (int i = 0; i < matches.size(); ++i) {
    //cout << "match of [" << i << "]: " << matches[i] << endl;
  //}
}
