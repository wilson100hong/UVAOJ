#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <assert.h>

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

//#define DEBUG

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
    cout << vec[i] << " ";
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
  void Relax(int root, int x);
  int LCA(int root, int x, int y);
  void Contract(int b, int x, int y, queue<int>& worklist);

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

  vector<int> Match() {
    matches_.assign(size_, NO_MATCH);
    for (int i = 0; i < size_; ++i) {
      if (matches_[i] == NO_MATCH) {
        ClearLocals();
        if (!BFS(i)) {
          state_[i] = IMPOSSIBLE;
        }
#ifdef DEBUG
        else {
          DumpVec("matches", matches_);
        }
#endif
      }
    }
    return matches_;
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
    DumpVec("color", color_);
    DumpVec("cross_1", cross_1);
    DumpVec("cross_2", cross_2);
  }

  // Local variables in BFS
  //queue<int> worklist;
  
  vector<int> state_;   // NO_VISIT, EVEN, ODD or IMPOSSIBLE
  vector<int> parent_;  // node's immediate parent node

  // nodes in same blossom has value equals to blossom root.
  vector<int> blossom_;
  vector<int> color_;
  vector<int> cross_1;
  vector<int> cross_2;
  
  // Global variables 
  vector<vector<int> > edges_;
  int size_;
  vector<int> matches_;
};

// -: unmatch
// =: match
//    root-.......g-p=x
// => root=.......g=p-x
void EdmondMatcher::Relax(int root, int x) {
#ifdef DEBUG
  cout << "Relax root: " << root << ", leaf: " << x << endl;
#endif 
  if (root == x) return;
  if (state_[x] == EVEN) {
    //cout << "EVEN:" << endl;
    int p = parent_[x];
    int g = parent_[p];
    Relax(root, g);
    matches_[p] = g;
    matches_[g] = p; 
  } else if (state_[x] == ODD) {
    //cout << "ODD:" << endl;
    Relax(matches_[x], cross_1[x]);
    Relax(root, cross_2[x]);
    matches_[cross_2[x]] = cross_1[x];
    matches_[cross_1[x]] = cross_2[x];
  } else {
    cout << "IMPOSSIBLE: " << state_[x];
  }
}

// Find the Least Common Ancestor of node x and y, given root.
int EdmondMatcher::LCA(int root, int x, int y) {

  // x and y should be in different blossom.
  int i = GetBlossom(x);  // i is the root of blossom x belongs
  int j = GetBlossom(y);  // j is the root of blossom y belongs
  assert(i != j);

  // NOTE: If we paint the root of blossom, all included nodes are painted
  //       because we always use GetBlossom(node) to compare color.
  // NOTE: since x and y are in different blossom, their root of blossom should
  // be colorless.
  // We let the path from i is RED, path from j is BLUE, then keep painting
  // util:
  // 1. i == j 
  // 2. path hits node with different color, such as
  //    a. color[i] is BLUE
  //    b. color[j] is RED
  while(i != j && color_[i] != BLUE && color_[j] != RED) {
    color_[i] = RED;
    color_[j] = BLUE;
    if (i != root)
      i = GetBlossom(parent_[i]);
    if (j != root)
      j = GetBlossom(parent_[j]);
  }

  // let b: root of blossom, 
  //     z: the node painted in this round which closest to root.
  //           ----x
  //  r---i--j/
  //          \--y    => color[i] is RED: z = i, b = j
  // 
  //           --x
  //  r---j--i/
  //          \----y  => color[i] is BLUE: z = j, b = i
  int z, b;
  if (color_[i] == RED) {
    z = i;
    b = j;
  } else {  // color[i] == BLUE
    z = j;
    b = i;
  }

  // We then all blossom root's color from b -> z, including b.
  for (i = b; i != z; i = GetBlossom(parent_[i])) {
    color_[i] = NO_COLOR;
  }
  color_[z] = NO_COLOR;

  // NOTE: we don't need to clear color from x -> b or y -> b,
  //       because GetBlossom(x) and GetBlossom(y)
  //       should return b and skip all colored nodes. This is smart!
  return b;
}

// Contract nodes into a blossom. B is the root of blossom, edge x-y is the
// cross edge.
void EdmondMatcher::Contract(int b, int x, int y, queue<int>& worklist) {
  for (int i = GetBlossom(x); i != b; i = GetBlossom(parent_[i])) {
    // i is either a) a not-contracted node or b) root of sub-blossom
    //Union(b, i);
    blossom_[i] = b;  // Union
    // The spirit of Contract is to "fan out" from ODD nodes because now ODD nodes
    // can be treat as EVEN nodes by cross edge. 
    // An ODD node is only handle once in Contract in one BFS.
    if (state_[i] == ODD) {
      // The meaning of cross edge:
      //    --i----x   => x is cross_1[i]
      //  b/    
      //   \--y        => y is cross_2[i]
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
      // If u and v are in same blossom, skip v because already processed.
      if (GetBlossom(u) == GetBlossom(v)) continue;

      // u and v are in different blossom.
      switch(state_[v]) {
        case NO_VISIT: {
          if (matches_[v] == NO_MATCH) { // v is EVEN and aug-path found
# ifdef DEBUG
            cout << endl;
            cout << "Find augmented path, root: " << root 
                 << ", u: " << u << ", v: " << v << endl;
            Dump();
#endif 
            Relax(root, u);
            matches_[u] = v;
            matches_[v] = u;
            return true;
          } else {  // v is matched so is ODD
            state_[v] = ODD;
            parent_[v] = u;
            // Extend w from v
            int w = matches_[v];
            state_[w] = EVEN;
            parent_[w] = v;
            worklist.push(w);
          }
        }
        break;

        case EVEN: {
#ifdef DEBUG
  cout << endl << "LCA for: {" << u << "," << v << "} with root: " << root << endl;
#endif
          int b = LCA(root, u, v);
          Contract(b, u, v, worklist);
          Contract(b, v, u, worklist);
#ifdef DEBUG
  cout << "blossom: " << b << endl;
#endif 
        }
        break;

        // Skip ODD because already processed.
        case ODD:
        // Skip IMPOSSIBLE because no aug-path can be found from this node.
        case IMPOSSIBLE:
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
 
  EdmondMatcher matcher(graph);
  vector<int> matches = matcher.Match();

  DumpVec("result", matches);
}
