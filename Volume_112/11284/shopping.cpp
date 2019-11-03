// 1. There can be multiple roads between two stores.
//
//
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iomanip>
using namespace std;

stringstream ss;


constexpr int kINF = numeric_limits<int>::max() / 4;

typedef vector<vector<int>> matrix;

stringstream& eatline() {
  string line;
  getline(cin, line);
  ss.clear();
  ss.str(line);
  return ss;
}

int str2int100(const string& str) {
  int v = 0;
  for (int i=0;i<str.size();++i) {
    if (str[i] == '.') {
      continue;
    }
    v = v*10 + (str[i] - '0');
  }
  return v;
}

string pad00(int x) {
  string y = to_string(x);
  while (y.size() < 2) {
    y = "0" + y;
  }
  return y;
}

struct DVD {
  int store;
  int price;  // *100
};

int sum_state_cost(const vector<int>& state_costs, int state) {
  int offset = 0;
  int sum = 0;
  while (state > 0) {
    if (state & 1) {
      sum += state_costs[offset];
    }
    state = state >> 1;
    offset++;
  }
  return sum;
}

int rec(const matrix& graph, const vector<int>& si_to_store, int store, int state, matrix& dp) {
  int N = graph.size();
  int M = si_to_store.size();
  if (dp[store][state] != kINF) {
    return dp[store][state];
  }

  // Iterate all possible next states.
  for (int m=0;m<M;++m) {
    if (state & (1 << m)) continue;

    int next = si_to_store[m];

    dp[store][state] = min(
        dp[store][state],  
        graph[store][next] + rec(graph, si_to_store, next, state | (1 << m), dp));
  }

  return dp[store][state];
}

void solve(const matrix& graph, const vector<DVD>& dvds) {
  int N = graph.size();
  // Groups dvd by store, as the state index (si).
  vector<int> store_to_si(N, -1);

  vector<int> si_costs;

  int total_at_home = 0;
  for (int i=0;i<dvds.size();++i) {
    int store = dvds[i].store;
    int si = store_to_si[store];
    if (si == -1) {
      si = store_to_si[store] = si_costs.size();
      si_costs.push_back(0);
    }
    si_costs[si] += dvds[i].price;
    total_at_home += dvds[i].price;
  }

  int M = si_costs.size();

  vector<int> si_to_store(M, -1);
  for (int i=0;i<N;++i) {
    if (store_to_si[i] != -1) {
      si_to_store[store_to_si[i]] = i;
    }
  }

  // Use DP.
  matrix dp(N, vector<int>(1<<M, kINF));
  // Initialize dp state.
  for (int i=0;i<N;++i) {
    dp[i][(1<<M)-1] = graph[i][0];
  }
  
  for (int state=0; state<(1<<M); ++state) {
    int paid = sum_state_cost(si_costs, state);
    dp[0][0] = min(dp[0][0], paid + rec(graph, si_to_store, 0, state, dp));
  }

  if (dp[0][0] == total_at_home) {
    cout << "Don't leave the house" << endl;
    return;
  }

  int saved = total_at_home - dp[0][0];
  cout << "Daniel can save $" << (saved / 100) << "." << setfill('0') << setw(2) << (saved % 100) << endl;
}

int main() {
  int T;
  eatline() >> T;
  while (T--) {
    eatline();
    int N, M;
    eatline() >> N >> M;

    // Number of nodes = N + 1 (including home).
    N++;
    matrix graph(N, vector<int>(N, kINF));
    for (int i=0;i<N;++i) {
      graph[i][i] = 0;
    }
    
    for (int m=0;m<M;++m) {
      int u, v;
      string cost_str;
      eatline() >> u >> v >> cost_str;
      int cost = str2int100(cost_str);
      if (cost < graph[u][v]) {
        graph[u][v] = graph[v][u] = cost;
      }
    }

    // Floyd Warshall for shortest distance between each pair of nodes.
    for (int k=0;k<N;++k) {
      for (int i=0;i<N;++i) {
        for (int j=0;j<N;++j) {
          graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
        }
      }
    }

    int P;
    eatline() >> P;
    vector<DVD> dvds;

    for (int p=0;p<P;++p) {
      int store;
      string cost_str;
      eatline() >> store >> cost_str;
      int price = str2int100(cost_str);
      dvds.push_back({store, price});
    }

    solve(graph, dvds);
  }
}
