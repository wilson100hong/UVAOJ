#include <iostream>
#include <map>
#include <vector>
#include <queue>

#define NMAX 30
#define NOT_VISIT -1

using namespace std;

int main() {
  int NC;
  bool network[NMAX][NMAX];
  int case_num = 1;
  while (cin >> NC) {
    if (NC == 0)
      break;
    // reset network
    for (int i = 0; i < NMAX; ++i) 
      for (int j = 0; j < NMAX; ++j)
        network[i][j] = (i == j ? true : false);
    map<int, int> n2i; // number to index
    vector<int> i2n;  // index to number
    int cnt = 0;
    while (NC-- > 0) {
      int from, to;
      cin >> from >> to;
      if (n2i.find(from) == n2i.end()) {
        n2i[from] = cnt++;
        i2n.push_back(from);
      }
      if (n2i.find(to) == n2i.end()) {
        n2i[to] = cnt++;
        i2n.push_back(to);
      }
      network[n2i[from]][n2i[to]] = network[n2i[to]][n2i[from]] = true;
    }
    int start, ttl;
    while (cin >> start >> ttl) {
      if (start == 0 && ttl == 0)
        break;
      // doing BFS
      int node = n2i[start];
      vector<int> visited;
      vector<int> ttl_remain(cnt, NOT_VISIT);
      ttl_remain[node] = ttl;
      queue<int> q;
      q.push(node);
      while (!q.empty()) {
        node = q.front();
        q.pop();
        visited.push_back(node);
        if (ttl_remain[node] > 0) {
          for (int nbr = 0; nbr < cnt; nbr++) {
            if (nbr != node && network[node][nbr] && ttl_remain[nbr] == NOT_VISIT) {
              ttl_remain[nbr] = ttl_remain[node] - 1;
              q.push(nbr);
            }
          }
        }
      }
      cout << "Case " << case_num++ << ": " << cnt - visited.size()
           << " nodes not reachable from node " << start
           << " with TTL = " << ttl << "." << endl;
    }
  }
}
