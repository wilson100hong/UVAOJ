#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

// 2016/11/06
// STAR: ****
// SKILL: extended euclidean
// TRAP:

typedef long long ll;

// return gcd(a, b) and x*a + y*b = gcd
ll egcd(ll a, ll b, ll& x, ll& y) {
  if (b > a) return egcd(b, a, y, x);
  ll r = a % b;
  ll q = a / b;
  if (r == 0) {
    x = 1;
    y = 1-q;
    return b;
  }
  ll x1, y1;
  ll g = egcd(b, a % b, x1, y1);
  x = y1;
  y = x1-q*y1;
  return g;
}

ll absl(ll n) {
  return n > 0 ? n : -n;
}

ll max(ll a, ll b) {
  return a > b ? a : b;
}

ll min(ll a, ll b) {
  return a < b ? a : b;
}

ll ceil(ll x, ll y) {
  return x/y + (x%y > 0);
}

struct Elevator {
  ll X;
  ll Y;
};

// return true if Y + n*X == F, n >= 0
bool stopat(const Elevator& e, ll floor) {
  return e.Y <= floor && (floor-e.Y) % e.X == 0;
}

struct Range {
  ll lb;  // lower bound
  ll ub;  // upper bound
};

// solve Range for n 
// 1. m+n*h >= 0
// 2. y + x*(m+n*h) <= floor
Range get_bound(ll m, ll h, ll floor, ll y, ll x) {
  ll lb, ub;
  // m+n*h2 >= 0:
  if (m >= 0) {
    lb = -1*(m/h);
  } else {
    lb = ceil(absl(m), h);
  }

  // y + x*(m+n*h) <= floor
  ll temp = (floor - y)/x - m;
  if (temp >= 0) {
    ub = temp / h;
  } else {
    ub = -1*ceil(absl(temp), h);
  }
  return {lb, ub};
}

// find (m1, m2) satisfy:
// 1. m1*x1+y1 = m2*x2+y2 => m1*x1 - m2*x2 = y2-y1
// 2. m1 >= 0 && m2 >= 0
// 3. m1*x1+y1 <= F && m2*x2+y2 <= F
bool connect(const Elevator& e1, const Elevator& e2, ll floor) {

  // first use extended euclidean to find k1*x1 + k2*x2 = gcd(x1, x2)
  ll x1 = e1.X, y1 = e1.Y, x2 = e2.X, y2 = e2.Y;
  if (y1 == y2) {
    return true;
  }
  ll k1, k2;
  ll g = egcd(x1, x2, k1, k2);
  
  if (absl(y2-y1) % g != 0) {
    return false;
  }
  ll mul = (y2-y1)/g;

  k1*=mul; k2*=mul;
  // now we have a pair (k1, k2) where k1*x1 + k2*x2 = y2-y1
  // but this is not enough because ki might not satisfy the requirement of mi
  ll m1 = k1, m2 = -1*k2;

  // now we have (m1, m2) m1*x1 - m2*x2 = y2-y1
  // adjust m1, m2 to make them in range
  // let h1*x1 = h2*x2
  ll h1 = x2/g, h2 = x1/g;
  
  Range r1 = get_bound(m1, h1, floor, y1, x1);
  Range r2 = get_bound(m2, h2, floor, y2, x2);

  /*
  DEBUG
  cout << "m1=" << m1 << endl;
  cout << "m2=" << m2 << endl;
  cout << "h1=" << h1 << endl;
  cout << "h2=" << h2 << endl;
  cout << "r1=" << r1.lb << "," << r1.ub << endl;
  cout << "r2=" << r2.lb << "," << r2.ub << endl;
  */
  
  return max(r1.lb, r2.lb) <= min(r1.ub, r2.ub);
}

void dfs(const vector<vector<int>>& graph, int node, vector<bool>& visit) {
  visit[node] = true;
  for (int next : graph[node]) {
    if (!visit[next]) {
      dfs(graph, next, visit);
    }
  }
}

bool has_path(const vector<vector<int>>& graph, int start, int end) {
  int n = graph.size();
  vector<bool> visit(n, false);
  dfs(graph, start, visit);
  return visit[end];
}

int main() {
  int N;
  ll F, E, A, B;
  cin >> N;

  while (N--) {
    cin >> F >> E >> A >> B;
    vector<vector<int>> graph(E+2, vector<int>());

    vector<Elevator> elvs;
    for (int i=0;i<E;++i) {
      ll X, Y;
      cin >> X >> Y;
      elvs.push_back({X, Y});
    }
    int start = E, end = E+1;
    for (int i=0;i<E;++i) {
      // add edge between elevators and start and end
      const Elevator& e1 = elvs[i];
      if (stopat(e1, A)) {
        graph[i].push_back(start);
        graph[start].push_back(i);
      }
      if (stopat(e1, B)) {
        graph[i].push_back(end);
        graph[end].push_back(i);
      }
      for (int j=i+1;j<E;++j) {
        const Elevator& e2 = elvs[j];
        if (connect(e1, e2, F)) {
          graph[i].push_back(j);
          graph[j].push_back(i);
        }
      }
    }
    // DEBUG
    /*
    int idx = 0;
    cout << start << endl;
    cout << end << endl;
    for (const auto& edges : graph) {
      cout << idx << ": ";
      for (int e : edges) {
        cout << e << ", ";
      }
      cout << endl;
      idx++;
    }
    */

    if (has_path(graph, start, end)) {
      cout << "It is possible to move the furniture." << endl;
    } else {
      cout << "The furniture cannot be moved." << endl;
    }
  }
}
