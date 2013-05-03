#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
using namespace std;

typedef pair<int, string> Edge;

map<string, set<Edge> > graph;
// station to connections name
map<string, string> connects;

void ParseRoute(string line) {
   string route = line.substr(0, 1);
   string last = "*";
   int index = 2;
   while (index < line.length()) {
      char c = line[index];
      string station;
      bool is_connect;
      if (c == '=') {
         station = line.substr(index + 1, 2);
         index += 3;
         is_connect = true;
      } else {
         station = route + line[index++];
         is_connect = false;
      }

      if (graph.find(station) == graph.end()) {
         set<Edge> edges;
         graph[station] = edges;
      }

      if (is_connect) {
         map<string, string>::iterator it1 = connects.find(last);
         map<string, string>::iterator it2 = connects.find(station);
         string conn;
         if (it1 != connects.end() && it2 != connects.end()) {
            string conn1 = it1->second;
            string conn2 = it2->second;
            if (conn1 != conn2) {
               // Build edges btw connections
               graph[conn1].insert(Edge(0, conn2));
               graph[conn2].insert(Edge(0, conn1));
            } // else don't care
         } else if (it1 != connects.end()) { // last found, but station miss
            string conn = it1->second;
            // Build edge from connection to station
            graph[conn].insert(Edge(0, station));
            // Build edge from station to connection
            graph[station].insert(Edge(3, conn));
            connects[station] = conn;
         } else if (it2 != connects.end()){ // station found, but last miss
            string conn = it2->second;
            // Build edge from connection to last 
            graph[conn].insert(Edge(0, last));
            // Build edge from last to connection
            graph[last].insert(Edge(3, conn));
            connects[last] = conn;
         } else {
            // Both not found
            string conn = "$" + last + station;
            set<Edge> edges;
            graph[conn] = edges;
            // Build edges from connection
            graph[conn].insert(Edge(0, station));
            graph[conn].insert(Edge(0, last));
            // Build edges from station/last to connection
            graph[last].insert(Edge(3, conn));
            graph[station].insert(Edge(3, conn));
            connects[last] = conn;
            connects[station] = conn;
         }
      } else {
         if (last != "*") {
            graph[last].insert(Edge(1, station));
            graph[station].insert(Edge(1, last));
         }
         last = station;
      }
   }
}

void DumpGraph() {
   map<string, set<Edge> >::iterator it;
   for (it = graph.begin(); it != graph.end(); ++it) {
      cout << it->first << " : ";
      set<Edge>::iterator vit;
      for (vit = it->second.begin(); vit != it->second.end(); ++vit)
         cout << "(" << vit->second << "," << vit->first << ")";
      cout << endl;
   }
}


map<string, int> dist;
map<string, string> prev;

void Dijkstra(string src) {
   dist.clear(); 
   prev.clear();
   dist[src] = 0;
   prev[src] = "*";
   set<Edge> Q;
   Q.insert(Edge(0, src));
   while (!Q.empty()) {
      Edge top = *Q.begin();
      Q.erase(Q.begin());
      int d = top.first;
      string u = top.second;

      set<Edge>::iterator it;
      for (it = graph[u].begin(); it != graph[u].end(); ++it) {
         int w = it->first;
         string v = it->second;
         if (dist.find(v) == dist.end() || (d + w < dist[v])) {
            if (dist.find(v) != dist.end()) 
               Q.erase(Edge(dist[v], v));   

            dist[v] = d + w;
            prev[v] = u;
            Q.insert(Edge(dist[v], v));
         } 
      }
   }
}

void ShortestRoute(string line) {
  string src = line.substr(0, 2);
  string dst = line.substr(2, 2);

  Dijkstra(src);
  cout.width(3);
  cout << dist[dst] << ": ";

  stack<string> path;
  while(dst != "*") {
     if (dst[0] != '$')
        path.push(dst);
     dst = prev[dst];
  }
  string station = path.top();
  path.pop();
  char route = station[0];
  cout << station;
  
  while (!path.empty()) {
     string station = path.top();
     path.pop();
     if (route == station[0]) {
       cout << station[1]; 
     } else {
       cout << "=" << station;
       route = station[0];
     }
  }
  cout << endl;
}

int main()  {
   int n;
   cin >> n;
   string line;
   getline(cin, line);
   graph.clear();
   connects.clear();
   for (int i = 0; i < n; ++i) {
      getline(cin, line);
      ParseRoute(line);
   }

   while (getline(cin, line) && line[0] != '#') 
     ShortestRoute(line);
}
