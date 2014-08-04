// TODO: better comments. On every non trival stuff

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>

using namespace std;

#define NO_MATCH -1
#define NO_PARENT -1
#define NO_CROSS -1

#define IMPOSSIBLE -2
#define NO_VISIT -1
#define EVEN 0 
#define ODD 1

#define NO_COLOR -1
#define RED 1
#define BLUE 2


class EdmondMatcher{
public:
  EdmondMatcher(const vector<set<int> >& edges_)
    : edges(edges_) {
    size = edges.size();
    matches.clear();
    for (int i = 0; i < size; ++i)
      matches.push_back(NO_MATCH);
  }

  vector<int> Match() {
    for (int i = 0; i < size; ++i) {
      if (matches[i] == NO_MATCH) {
        ClearLocals();
        if (!BFS(i)) {
          state[i] = IMPOSSIBLE;
        }
      }
    }
    return matches;
  }

  void ClearLocals() {
    state.assign(size, UNVISITED);
    parent.assign(size, NO_PARENT);
    blossom.clear();
    for (int i = 0; i < size; ++i) {
      blossom.push_back(i);
    }
    while (!worklist.empty()) {
      worklist.pop();
    }
    color.assign(size, NO_COLOR);
  }

  int GetBlossom(int x) {
    // Also recursively update blossom
    if (x != blossom[x])
      blossom[x] = GetBlossom(parent[x]);
    return blossom[x];
  }

  void Union(int b, int x) {
    blossom[x] = b;
  }

  void BFS(int root);
  void AlterPath(int root, int x);
  int LCA(int root, int x, int y);
  void Contract(int b, int x, int y);

  // Local variables in BFS
  queue<int> worklist;
  // NO_VISIT, EVEN or ODD
  vector<int> state;
  // nodes immediate parent
  vector<int> parent;
  // nodes in same blossom has value equals to blossom root.
  vector<int> blossom;
  vector<int> color;
  vector<int> cross_1;
  vector<int> cross_2;
  
  // Global variables 
  vector<set<int> > edges;
  int size;
  vector<int> matches;
};

void EdmondMatcher::AlterPath(int root, int x) {
  if (root == x) return;
  // -: unmatch
  // =: match
  //    r.......g-p=x
  // => r.......g=p-x
  // but we don't need to handle x
  if (state[x] == EVEN) {
    int p = parent[x];
    int g = parent[p];
    AlterPath(g);
    matches[p] = g;
    matches[g] = p; 
  } else if (state[x] == ODD) {
    AlterPath(cross_1[x], matches[x]);
    AlterPath(root, cross_2[x]);
    matches[cross_2[x]] = corss_1[x];
    matches[corss_1[x]] = cross_2[x];
  } else {
    cout << "IMPOSSIBLE: " << state[x];
  }
}

int EdmondMatcher::LCA(int root, int x, int y) {
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
      i = GetBlossom(parent[i]);
    if (j != root)
      j = GetBlossom(parent[j]);
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
  for (i = b; i != z; i = GetBlossom(parent(i))) {
    color[i] = NO_COLOR;
  }
  color[z] = NO_COLOR;

  // we don't need to clear b->x and b->y, because GetBlossom(x) and GetBlossom(y)
  // should return b and skip all colored nodes. This is smart!
  return b;
}


void EdmondMatcher::Contract(int b, int x, int y) {
  for (int i = GetBlossom(x); i != b; i = GetBlossom(parent[i])) {
    // here i is either a nodde not contracted or the blossom root
    Union(b, i);
    // An ODD node n is only handled once here: when it is contracted the first time.
    // It will never be considered later.
    // 1. GetBlossom(n) never return the n. It will return the blossom root instead
    // 2. BFS never push n into worklist.
    if (state[i] == ODD) {
      //    --i----x      c1[i] = x
      //  b/   
      //   \--y        => c2[i] = y
      cross_1[i] = x;
      cross_2[i] = y;
      worklist.push(i);
    }
  }
}

// Return true if find 
bool EdmondMatcher::BFS(int root) {
  state[root] = EVEN;
  parent[root] = root;

  worklist.push(root);
  while (!worklist.empty()) {
    int u = worklist.front();
    worklist.pop();
    for (int i = 0; i < edges[u]; ++i) {
      int v = edges[u][i];
      // If u and v are in the same blossom, skip v
      // because v must has been processed before.
      if (GetBlossom(u) == GetBlossom(v)) continue;

      // u and v are in different blossom.
      switch(state[v]) {
        case UNVISITED: {
          if (matches[v] == NO_MATCH) {
            // EVEN, and find aug path
            AlterPath(root, u);
            matches[u] = v;
            matches[v] = u;
            return true;
          } else {
            // ODD
            state[v] = ODD;
            parent[v] = u;
            int w = matches[v];
            state[w] = EVEN;
            parent[w] = v;
            worklist.push(w);
          }
        }
        break;
        case EVEN: {
          int b = LCA(root, x, y);
          Contract(b, x, y);
          Contract(b, y, x);
        }
        break;
        case ODD:  // skip
        case IMPOSSIBLE:   // skip
        case default:
        break;
      }
    }
  }
  return false;
}
