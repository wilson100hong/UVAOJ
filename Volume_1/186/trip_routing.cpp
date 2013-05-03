#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

void Tokenize(const string& line,
              string& city1_name,
              string& city2_name) {
  stringstream ss(line);
  getline(ss, city1_name, ',');
  getline(ss, city2_name, ',');
}
void Tokenize(const string& line,
              string& city1_name,
              string& city2_name,
              string& road_name,
              int& cost) {
  stringstream ss(line);
  getline(ss, city1_name, ',');
  getline(ss, city2_name, ',');
  getline(ss, road_name, ',');
  ss >> cost;
}

#define N_MAX 100
#define NO_ROAD -1
#define NO_NEXT -1
#define INF 1<<20

map<string, int> city_map;
vector<string> city_names;
map<string, int> road_map;
vector<string> road_names;
int dist[N_MAX][N_MAX];
int next[N_MAX][N_MAX];
int roads[N_MAX][N_MAX];

void Padding(string s, int width) {
  width -= s.length();
  cout << s;
  while (width-- > 0)
    cout << " ";
}

void DumpRoad(int src, int dst) {
  Padding(city_names[src], 20);
  cout << " ";
  Padding(city_names[dst], 20);
  cout << " ";
  Padding(road_names[roads[src][dst]], 10);
  cout << " ";
  cout.width(5);
  cout << dist[src][dst] << endl;
}

void GetPath(int src, int dst) {
  if (dist[src][dst] == INF) {
    cout << "IMPOSSIBLE" << endl;
    return;
  }
  int intermediate = next[src][dst];
  if (intermediate == NO_NEXT) {
    DumpRoad(src, dst);
  } else {
    GetPath(src, intermediate);
    GetPath(intermediate, dst);
  }
}

int main() {
  string line;
  // 0. Initialize dp arrays
  for (int i=0; i<N_MAX; ++i)
    for (int j=0; j<N_MAX; ++j) {
      roads[i][j] = NO_ROAD;
      dist[i][j] = INF;
      next[i][j] = NO_NEXT;
    }
  for (int i = 0; i < N_MAX; ++i)
    dist[i][i] = 0;

  while(getline(cin, line)) {
    if (line == "")
      break;
    string city1_name, city2_name, road_name;
    int cost;
    // 1. Tokenize line into c1_name, c2_name, road_name, cost
    Tokenize(line, city1_name, city2_name, road_name, cost);

    // 2. Add new cities if necessary
    if (city_map.find(city1_name) == city_map.end()) {
      city_map[city1_name] = city_names.size();
      city_names.push_back(city1_name);
    }
    if (city_map.find(city2_name) == city_map.end()) {
      city_map[city2_name] = city_names.size();
      city_names.push_back(city2_name);
    }

    // 3. Add new roads if necessary
    if (road_map.find(road_name) == road_map.end()) {
      road_map[road_name] = road_names.size();
      road_names.push_back(road_name);
    }

    // 4. mark roads and dist
    int src = city_map[city1_name], dst = city_map[city2_name];
    if (cost < dist[src][dst]) {
      roads[src][dst] = road_map[road_name];
      roads[dst][src] = road_map[road_name];
      dist[src][dst] = cost; dist[dst][src] = cost;
    }
  }

  int N = city_names.size();

  // TEST
  /*for (int i=0; i<city_names.size(); ++i)
    cout << i << " : " << city_names[i] << endl;
  for (int i=0; i<N; ++i) {
    for (int j=0;j<N; ++j) {
      int r = roads[i][j];
      if (r != NO_ROAD)
        cout << road_names[r] << ", ";
      else
        cout << "X ,";
    }
    cout << endl;
  }
  */

  // 5. Do Floyd-warshall here, and also the next_table
  for (int k = 0; k < N; ++k)
    for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next[i][j] = k;
        }
      }
  // TEST
  /*
  for (int i=0; i<N; ++i) {
    for (int j=0;j<N; ++j) {
      int d = dist[i][j];
      if (d != INF)
        cout << d << ", ";
      else
        cout << "X ,";
    }
    cout << endl;
  }
  */

  while (getline(cin, line)) {
    // 6. Tokenize src city and dst city
    string city1_name, city2_name;
    Tokenize(line, city1_name, city2_name);
    // 7. Retrieve paths from cost_table and next_table
    int src = city_map[city1_name], dst = city_map[city2_name];

    // 8. Dump result
    cout << endl << endl;
    cout << "From                 To                   Route      Miles" << endl;
    cout << "-------------------- -------------------- ---------- -----" << endl;
    GetPath(src, dst);
    cout << "                                                     -----" << endl;
    cout << "                                          Total      ";
    cout.width(5);
    cout << dist[src][dst] << endl;
  }
}
