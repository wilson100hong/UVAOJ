#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> Point;

#define INF -1.f

double distance(const Point& p1, const Point& p2) {
  double dx = p1.first - p2.first;
  double dy = p1.second - p2.second;
  return sqrt(dx*dx + dy*dy);
}

vector<bool> visit;
void dfs(const vector<vector<double>>& graph,
    int u, vector<int>* state, double thld) {
  visit[u] = true;
  state->push_back(u);
  for (int v = 0; v < graph[u].size(); ++v) {
    if (!visit[v] && graph[u][v] <= thld) {
      dfs(graph, v, state, thld);
    }
  }
}

typedef pair<double, int> DI;
double prim(const vector<vector<double>>& graph) {
  set<DI> heap;
  heap.insert(make_pair(0.f, 0));
  double sum = 0;
  
  map<int, double> distance;
  set<int> connected;
  int n = graph.size();
  while (!heap.empty() && connected.size() < n) {
    DI top = *heap.begin();
    heap.erase(top);

    int u = top.second;
    if (connected.count(u) > 0) continue;  // already connected

    // this is a new node!
    connected.insert(u);
    distance[u] = top.first;
    sum += distance[u];
    
    for (int v = 0; v < graph[u].size(); ++v) {
      if (v != u && connected.count(v) == 0) {
        double d = graph[u][v];
        if (distance.count(v) == 0) {
          distance[v] = d;
          heap.insert(make_pair(d, v));
        } else if (d < distance[v]) {   // distance.count(v) != 0
          heap.erase(make_pair(distance[v], v));
          heap.insert(make_pair(d, v));
          distance[v] = d;
        }
      }
    }
  }
  return sum;
}

void solve(const vector<Point>& points, int thld) {
  // 1. build graph 
  vector<vector<double>> graph(points.size(), vector<double>(points.size(), 0.f));
  for (int i = 0; i < points.size(); ++i) {
    for (int j = i + 1; j < points.size(); ++j) {
      graph[i][j] = graph[j][i] = distance(points[i], points[j]);
    }
  }
  // 2. count state 
  vector<vector<int>> states;
  vector<int> city2state(points.size(), -1);
  visit.clear();  visit.assign(points.size(), false);
  for (int i = 0; i < points.size(); ++i) {
    vector<int> state;
    if (!visit[i]) {
      dfs(graph, i, &state, thld);
      for (int city : state) {
        city2state[city] = states.size();
      }
      states.push_back(state);
    }
  }

  // 3. for each state, doing MST
  double cost_road = 0.0;
  for (const vector<int>& state : states) {
    // construct state graph
    vector<vector<double>> state_graph(state.size(), vector<double>(state.size(), 0.f));
    for (int i = 0; i < state.size(); ++i) {
      for (int j = i + 1; j < state.size(); ++j) {
        state_graph[i][j] = state_graph[j][i] = graph[state[i]][state[j]];
      }
    }
    cost_road += prim(state_graph);
  }
  int rd = static_cast<int>(cost_road + 0.5);

  // 4. MST for rails 
  // construct federal graph
  vector<vector<double>> federal_graph(states.size(), vector<double>(states.size(), INF));
  // loop for all edges
  for (int i = 0; i < points.size(); ++i) {
    for (int j = i + 1; j < points.size(); ++j) {
      double d = graph[i][j];
      int si = city2state[i], sj = city2state[j];
      if (si != sj) {
        if (federal_graph[si][sj] == INF || federal_graph[si][sj] > d) {
          federal_graph[si][sj] = federal_graph[sj][si] = d;
        }
      }
    }
  }
  double cost_rails = prim(federal_graph);
  int rl = static_cast<int>(cost_rails + 0.5);

  // round to closest integer for cost_rails, cost_roads
  cout << " " << states.size() << " " << rd << " " << rl << endl;
}

int main() {
  int T;
  cin >> T;
  for (int tc = 1; tc <= T; ++tc) {
    int n, r;
    cin >> n >> r;
    vector<Point> points;
    for (int i = 0; i < n; ++i) {
      int x, y;
      cin >> x >> y;
      points.push_back(make_pair(x, y));
    }

    cout << "Case #" << tc << ":";
    solve(points, r);
  }
}
