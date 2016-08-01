#include <iostream>
#include <vector>
#include <sstream>
#include <set>

using namespace std;

int max(int a, int b) {
  return a > b ? a : b;
}

int str_to_10xint(const string& s) {
  int n = 0;
  for (char c : s) {
    if (c == '.') continue;
    n = n * 10 + (c - '0');
  }
  return n;
}

string int_to_decstr(int n) {
  stringstream ss;
  ss << (n / 10) << "." << (n % 10);
  return ss.str();
}

bool eatline(stringstream& ss) {
  string line;
  if (getline(cin, line)) {
    ss.clear();
    ss.str(line);
    return true;
  } else {
    return false;
  }
}

struct Path {
  int dest;
  int length;
  int temp;
};
typedef vector<vector<Path>> Graph;

void print(const Graph& graph) {
  int s = 0;
  for (const auto& edges : graph) {
    cout << "S = " << s << endl;
    for (const auto& path : edges) {
      cout << path.dest << " " << path.length << " " <<  path.temp << endl;
    }
    s++;
  }
}

typedef pair<int, int> II;

int MAX_TEMP = 100000;
int dijkstra_temp(const Graph& graph, int s, int t) {
  int n = graph.size();
  set<II> heap;  // temp - index
  vector<int> temp(n, MAX_TEMP);

  temp[s] = 0;
  heap.insert(II(temp[s], s));

  while (!heap.empty()) {
    II top = *heap.begin();
    if (top.second == t) break;

    heap.erase(top);
    int u = top.second;
    int cur_temp = top.first;
    for (const Path& path : graph[u]) {
      int v = path.dest;
      int new_temp = max(path.temp, cur_temp);
      if (new_temp < temp[v]) {
        if (temp[v] != MAX_TEMP) {
          heap.erase(II(temp[v], v));
        }
        temp[v] = new_temp;
        heap.insert(II(new_temp, v));
      }
    }
  }
  return temp[t];
}

int MAX_DIST = 10000000;
int dijkstra_route(const Graph& graph, int s, int t, int max_temp) {
  int n = graph.size();
  set<II> heap;  // distance - index
  vector<int> dist(n, MAX_DIST); 
  vector<int> parent(n, -1);

  dist[s] = 0;
  heap.insert(II(dist[s], s));
  while (!heap.empty()) {
    II top = *heap.begin();
    heap.erase(top);

    int u = top.second;
    if (u == t) 
      break;
    int cur_dist = top.first;
    for (const Path& path : graph[u]) {
      if (path.temp > max_temp) 
        continue;
      int v = path.dest;
      int new_dist = cur_dist + path.length;
      if (new_dist < dist[v]) {
        if (dist[v] != MAX_DIST) {
          heap.erase(II(dist[v], v));
        }
        heap.insert(II(new_dist, v));
        dist[v] = new_dist;
        parent[v] = u;
      }
    }
  }

  vector<int> route;
  int c = t;
  while (parent[c] != -1) {
    route.push_back(c);
    c = parent[c];
  }
  route.push_back(c);
  
  bool space = false;
  for (auto it = route.rbegin(); it != route.rend(); ++it) {
    if (space) cout << " ";
    cout << *it;
    space = true;
  }
  cout << endl << int_to_decstr(dist[t]) << " " << int_to_decstr(max_temp) << endl;
}

void solve(const Graph& graph, int s, int t) {
  // 1. find best_temp
  int max_temp = dijkstra_temp(graph, s, t);
  // 2. use best_temp to find minimum distance from s to t
  dijkstra_route(graph, s, t, max_temp);
}

int main() {
  stringstream ss;
  while (eatline(ss)) {
    int N, E;
    ss >> N >> E;
    // 1-based index
    Graph graph(N + 1, vector<Path>());
    int S, T;
    eatline(ss);
    ss >> S >> T;
    for (int e = 0; e < E; ++e) {
      int X, Y;
      string _R, _D;
      eatline(ss);
      ss >> X >> Y >> _R >> _D;
      Path path = {Y, str_to_10xint(_D), str_to_10xint(_R)}; 
      graph[X].push_back(path);
      path.dest = X;
      graph[Y].push_back(path);
    }
    solve(graph, S, T);
  }
}
