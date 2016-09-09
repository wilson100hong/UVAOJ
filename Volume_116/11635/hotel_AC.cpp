// This problem is not hard in algorithm. But has many tricky optimizations
// to solve TLE issues.
// 
// Algorithm has two passes. In 1st pass, do Dijkstra for all hotels (and also
// start and end points). Don't use Floyd-warshall! It's too slow.
// In each Dijkstra we get a list of "accessible" adjacents hotels
// which has distance <= 600. It will give you a new graph, where each node
// is hotel (or start, or end point). And edges exists between nodes which cost <= 600.
// Each edge has weight 1 mean it cost one sleep.
// In 2nd pass do BFS from starting point. The distance from start point to end point minus
// one is the answer. Or -1 if not connected.
//
// The exciting part is the optimizations. Although its very fast on my computer, without
// the folllowing works it still cause LTE.
// 1. (Re-)use global variables, like arrays 
// 2. Use adjacent list (vector) for roads. Don't use array, because initialize 
//    a int[10000][10000] array is super expensive.
// 3. avoid using STL map with N elements. too slow
// 4. magic IO: ios::sync_with_stdio(false);
#include <iostream>
#include <ios>
#include <set>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

int MH = 600;
int INF = numeric_limits<int>::max() / 4;

int N = 0;
#define MAX_N 10005

struct Edge {
  int to;
  int cost;
};
vector<Edge> ROADS[MAX_N];

int H = 0;
int HSTART = -1;
int HEND = -1;
#define MAX_H 105
int HOTELS[MAX_H];
vector<int> NEIGHBORS[MAX_H];

typedef pair<int, int> II;
void  dijkstra(int start, int hindex) {
  // return neighbors in nodes which shortest distance <= MH
  int dist[MAX_N];
  for (int i=1; i<=N; ++i) {
    dist[i] = INF;
  }
  dist[start] = 0;
  
  set<II> heap;
  heap.insert(II(0, start));
  while (!heap.empty()) {
    II top = *heap.begin();
    heap.erase(top);
    if (top.first > MH) {
      // rest nodes > MH, early exit
      break;
    }
    int cur = top.second;
    const vector<Edge>& edges = ROADS[cur];

    for (const Edge& edge : edges) {
      int to = edge.to;
      int ndist = dist[cur] + edge.cost;
      if (ndist < dist[to]) {
        dist[to] = ndist;
        if (dist[to] != INF) {
          heap.erase(II(dist[to], to));
        }
        heap.insert(II(ndist, to));
      }
    }
  }

  NEIGHBORS[hindex].clear();
  for (int h=0; h<H; ++h) {
    int hotel=HOTELS[h];
    if (hotel != start && dist[hotel] <= MH) {
      NEIGHBORS[hindex].push_back(h);
    }
  }
}


void solve() {
  for (int h=0; h<H; ++h) {
    dijkstra(HOTELS[h], h);
  }
  
  // BFS from HSTART
  queue<int> waiting;
  
  int hops[MAX_H];
  for (int h=0;h<H;++h){
    hops[h] = -1;
  }

  hops[HSTART] = 0;
  waiting.push(HSTART);
  while (!waiting.empty()) {
    int cur = waiting.front();
    waiting.pop();

    vector<int>& neighbors = NEIGHBORS[cur];
    for (int next: neighbors) {
      if (hops[next] == -1) {
        hops[next] = hops[cur] + 1;

        waiting.push(next);
      }
    }
  }
  int ans = hops[HEND] == -1 ? -1 : hops[HEND]-1;
  cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  while (1) {
    cin >> N;
    if (N == 0) break;
    cin >> H;
    HSTART = HEND = -1;
    for (int h=0; h<H; ++h) {
      int hotel;
      cin >> hotel;
      if (hotel == 1) {
        HSTART = h;
      } else if (hotel == N) {
        HEND = h;
      }
      HOTELS[h] = hotel;
    }

    if (HSTART == -1) {
      HSTART = H;
      HOTELS[H++] = 1;
    }
    if (HEND == -1) {
      HEND = H;
      HOTELS[H++] = N;
    }

    for (int i=0; i<=N; ++i) {
      ROADS[i].clear();
    }
    int nr;
    cin >> nr;
    for (int i=0; i<nr; ++i) {
      int ca, cb, t;
      cin >> ca >> cb >> t;
      ROADS[ca].push_back({cb, t});
      ROADS[cb].push_back({ca, t});
    }

    solve();
  }
}
