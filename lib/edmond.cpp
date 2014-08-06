// TODO: better comments. On every non trival stuff

#include <iostream>
#include <map>
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
  EdmondMatcher(const vector<vector<int> >& edges_)
    : edges(edges_) {
    size = edges.size();
    matches.clear();
    for (int i = 0; i < size; ++i)
      matches.push_back(NO_MATCH);
  }

  bool BFS(int root);
  void AlterPath(int root, int x);
  int LCA(int root, int x, int y);
  void Contract(int b, int x, int y);

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
    cout << "Clear locals" << endl;
    state.assign(size, NO_VISIT);
    parent.assign(size, NO_PARENT);
    blossom.clear();
    for (int i = 0; i < size; ++i) {
      blossom.push_back(i);
    }
    while (!worklist.empty()) {
      worklist.pop();
    }
    color.assign(size, NO_COLOR);
    cross_1.assign(size, NO_CROSS);
    cross_2.assign(size, NO_CROSS);
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
  vector<vector<int> > edges;
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
    AlterPath(root, g);
    matches[p] = g;
    matches[g] = p; 
  } else if (state[x] == ODD) {
    AlterPath(cross_1[x], matches[x]);
    AlterPath(root, cross_2[x]);
    matches[cross_2[x]] = cross_1[x];
    matches[cross_1[x]] = cross_2[x];
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
  for (i = b; i != z; i = GetBlossom(parent[i])) {
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
    for (int i = 0; i < edges[u].size(); ++i) {
      int v = edges[u][i];
      // If u and v are in the same blossom, skip v
      // because v must has been processed before.
      if (GetBlossom(u) == GetBlossom(v)) continue;

      // u and v are in different blossom.
      switch(state[v]) {
        case NO_VISIT: {
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
          int b = LCA(root, u, v);
          Contract(b, u, v);
          Contract(b, v, u);
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

vector<int> MakeVec(int array[], int cnt) {
  return vector<int>(array, array + cnt);
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
 
  for (int i = 0; i < graph.size(); ++i) {
    cout << graph[i].size() << endl;
  }

  EdmondMatcher matcher(graph);
  cout << "start match:" << endl;
  vector<int> matches = matcher.Match();

  cout << "match result:" << endl;
  for (int i = 0; i < matches.size(); ++i) 
    cout << "match of [" << i << "]: " << matches[i] << endl;
}
