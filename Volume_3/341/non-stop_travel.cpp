#include <iostream>
#include <vector>
#include <set>
#include <utility>

using namespace std;

#define MAX 12  // 0 not used. use 1 ~ 10
#define INF 1 << 30
#define IMPOSSIBLE -1

int N;  // number of nodes
int dist[MAX];
int parent[MAX];
int edges[MAX][MAX];

void Clear() {
  for (int i = 0; i < MAX; ++i) {
    for (int j = 0; j < MAX; ++j) {
      edges[i][j] = IMPOSSIBLE;
    }
    dist[i] = INF; 
    parent[i] = i;
  }
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
    int d = top.first;
    for (int to = 1; to <= N; ++to) {
      if (edges[from][to] != IMPOSSIBLE &&
          d + edges[from][to] < dist[to]) {
        if (dist[to] != INF) {
          heap.erase(heap.find(ii(dist[to], to)));
        }
        dist[to] = d + edges[from][to];
        heap.insert(ii(dist[to], to));
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
    Clear();
    for (int from = 1; from <= N; ++from) {
      int num_edges;
      cin >> num_edges;
      for (int i = 0; i < num_edges; ++i) {
        int to;
        cin >> to;
        cin >> edges[from][to];
      }
    }
    int start, end;
    cin >> start >> end;
    Solve(round++, start, end);
  }
}
