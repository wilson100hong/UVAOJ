#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

#define MAX 10 + 1  // 0 not used. use 1 ~ 10
#define INF 1 << 30
#define IMPOSSIBLE -1

int N;  // number of nodes
int dist[MAX];
int parent[MAX];
int edges[MAX][MAX];
string line;  // dummy

void Clear() {
  for (int i = 0; i < MAX; ++i) {
    for (int j = 0; j < MAX; ++j) {
      edges[i][j] = IMPOSSIBLE;
    }
    dist[i] = INF; 
    parent[i] = i;
  }
}

void DumpState() {
  cout << "dist: " << endl;
  for (int i = 1; i <= N; ++i) {
    cout << dist[i] << ", ";
  }
  cout << endl;
}

void DumpEdges() {
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      cout << edges[i][j] << ", ";
    }
    cout << endl;
  }
  cout << endl;
}

typedef pair<int, int> ii;

void Solve(int round, int start, int end) {
  dist[start] = 0;
  set<ii> heap;
  heap.insert(ii(0, start));
 
  while (!heap.empty()) {
    ii top = *heap.begin();
    heap.erase(heap.begin());
    int from = top.second;
    if (from == end) break;

    int cost = top.first;
    for (int to = 1; to <= N; ++to) {
      int new_dist = cost + edges[from][to];
      if (edges[from][to] != IMPOSSIBLE &&
          new_dist < dist[to]) {
        if (dist[to] != INF) {
          heap.erase(heap.find(ii(dist[to], to)));
        }
        heap.insert(ii(new_dist, to));
        dist[to] = new_dist;
        parent[to] = from;
      }
    }
  }
  vector<int> path;
  int cursor = end;
  do {
    path.push_back(cursor);
    cursor = parent[cursor];
  } while (cursor != parent[cursor]);
  path.push_back(start);
  
  cout << "Case " << round << ": Path =";
  for (int i = path.size() - 1; i >= 0; --i) 
    cout << " " << path[i];
  cout << "; " << dist[end] << " second delay" << endl;
}

int main() {
  int round = 1;
  while (cin >> N) {
    if (N == 0)  break;
    getline(cin, line);

    Clear();
    for (int from = 1; from <= N; ++from) {
      int num_edges;
      cin >> num_edges;
      for (int i = 0; i < num_edges; ++i) {
        int to;
        cin >> to;
        cin >> edges[from][to];
      }
      getline(cin, line);
    }
    int start, end;
    cin >> start >> end;
    getline(cin, line);
    getline(cin, line);  // Empty line in between
    //DumpEdges();
    Solve(round, start, end);
    round++;
  }
}

