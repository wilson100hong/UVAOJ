// TODO: TLE
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

int MH = 600;
int INF = numeric_limits<int>::max() / 4;

typedef pair<int, int> II;
set<int> dijkstra(const set<int>& nodes, const vector<vector<int>>& roads, int start) {
  // return neighbors in nodes which shortest distance <= MH

  int N = roads.size()-1;
  vector<int> dist(N+1, INF);
  dist[start] = 0;
  // for now, find shortest distances to all nodes.
  set<II> heap;
  heap.insert(II(0, start));
  while (!heap.empty()) {
    II top = *heap.begin();
    heap.erase(top);
    int cur = top.second;
    for (int next=1; next<=N; ++next) {
      if (next == cur) continue;
      if (roads[cur][next] != INF) {
        int ndist = dist[cur] + roads[cur][next];
        if (ndist < dist[next]) {
          if (dist[next] != INF) {
            heap.erase(II(dist[next], next));
          }
          dist[next] = ndist;
          heap.insert(II(ndist, next));
        }
      }
    }
  }

  set<int> good;
  for (int node : nodes) {
    if (node != start && dist[node] <= MH) {
      good.insert(node);
    }
  }
  return good;
}

void solve(int N, const set<int>& hotels, const vector<vector<int>>& roads) {
  int start = 1;
  int dest = N;
  set<int> nodes = hotels;
  nodes.insert(start);
  nodes.insert(dest);

  map<int, set<int>> graph;
  for (int node : nodes) {
    set<int> neighbors = dijkstra(nodes, roads, node);
    graph[node] = neighbors;
  }

  // BFS from 1, end at dest
  queue<int> waiting;
  map<int, int> hops;
  hops[1] = 0;

  waiting.push(1);
  while (!waiting.empty()) {
    int cur = waiting.front();
    waiting.pop();
    for (int neighbor : graph[cur]) {
      if (hops.count(neighbor) == 0) {
        hops[neighbor] = hops[cur] + 1;
        waiting.push(neighbor);
      }
    }
  }
  if (hops.count(N) == 0) {
    cout << "-1" << endl;
  } else {
    cout << hops[N] - 1 << endl;
  }
}

int main() {
  int N;
  while (1) {
    cin >> N;
    if (N == 0) break;
    set<int> hotels;
    int nh;
    cin >> nh;
    for (int i=0; i<nh; ++i) {
      int hotel;
      cin >> hotel;
      hotels.insert(hotel);
    }
    int nr;
    cin >> nr;
    vector<vector<int>> roads(N+1, vector<int>(N+1, INF));
    for (int i=1; i<=N; ++i) {
      roads[i][i] = 0;
    }
    for (int i=0; i<nr; ++i) {
      int ca, cb, t;
      cin >> ca >> cb >> t;
      if (t < roads[ca][cb]) {
        roads[ca][cb] = roads[cb][ca] = t;
      }
    }
    solve(N, hotels, roads);
  }
}
