// NOTE:
// (1) vector.size() - 1 could be big positive number if vector.size() == 0!
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
#include <math.h>
using namespace std;

struct Tree {
  int x;
  int y;
  int value;
  int len;
  int index;  // used for printing answer only
};

struct Vec2D {
  int x;
  int y;
};

int CompareTree(const Tree& t1, const Tree& t2) {
  if (t1.x == t2.x) 
    return t1.y < t2.y;
  else
    return t1.x < t2.x;
}

double Dist(const Tree& t1, const Tree& t2) {
  double dx = static_cast<double>(t1.x-t2.x);
  double dy = static_cast<double>(t1.y-t2.y);
  return sqrt(dx*dx + dy*dy);
}

int Cross(const Tree& o, const Tree& a, const Tree& b) {
  Vec2D oa = {a.x-o.x, a.y-o.y};
  Vec2D ob = {b.x-o.x, b.y-o.y};
  return oa.x*ob.y - oa.y*ob.x;
}

double Contour(const vector<Tree>& sorted, const vector<bool>& cuts) {
  // Convext hull
  int n = sorted.size();
  vector<Tree> ctrs(2*n);
  int k = 0;
  // bottom half
  for (int i=0; i<n; ++i) {
    if (cuts[sorted[i].index]) continue;
    while (k >= 2 && Cross(ctrs[k-2], ctrs[k-1], sorted[i]) <= 0) k--;
    ctrs[k++] = sorted[i];
  }
  // top half
  for (int i=n-2, t=k+1; i>=0; --i) {
    if (cuts[sorted[i].index]) continue;
    while (k >= t && Cross(ctrs[k-2], ctrs[k-1], sorted[i]) <= 0) k--;
    ctrs[k++] = sorted[i];
  }
  ctrs.resize(k);
  
  double sum = 0.f;
  for (int i=0; i+1<ctrs.size(); ++i) {
    sum += Dist(ctrs[i], ctrs[i+1]);
  }
  return sum;
}

struct Result {
  vector<bool> cuts;
  int dead;  // number of trees get cut
  int value;
  double extra;
};

Result Best(
    const vector<Tree>& trees,
    const vector<Tree>& sorted,
    int cur,
    const vector<bool>& cuts,  
    int dead,
    int value,
    double lumber) {
  double cost = Contour(sorted, cuts);
  Result res = {cuts, dead, value, lumber-cost};

  if (res.extra >= 0.f || cur >= trees.size()) {
    return res;
  }
  
  vector<bool> ncuts(cuts);
  for (int ncut = cur; ncut < cuts.size(); ++ncut) {
    ncuts[ncut] = true;
    Result tr = Best(trees, sorted, ncut+1, ncuts, dead+1, value+trees[ncut].value, lumber+trees[ncut].len);
    if (tr.extra >= 0.0) {
      if (res.extra < 0.0
          || (tr.value < res.value
              || (tr.value == res.value && tr.dead < res.dead))) {
        res = tr;
      }
    }
    ncuts[ncut] = false;
  }
  return res;
}

void Solve(const vector<Tree>& trees) {
  vector<Tree> sorted(trees);
  sort(sorted.begin(), sorted.end(), CompareTree);

  vector<bool> cuts(trees.size(), false);
  Result result = Best(trees, sorted, 0, cuts, 0, 0.f, 0.f);

  cout << "Cut these trees:";
  for (int i=0; i<result.cuts.size(); ++i) {
    if (result.cuts[i]) cout << " " << i+1;
  }
  cout << endl;

  cout << std::fixed << std::setprecision(2) << "Extra wood: " << result.extra << endl;
}

int main () {
  int n;
  int round = 1;
  while (cin >> n) {
    if (n == 0) break;
    int x, y, v, l;
    vector<Tree> trees;
    for (int i=0; i<n; ++i) {
      cin >> x >> y >> v >> l;
      trees.push_back({x, y, v, l, i});
    }

    if (round > 1) cout << endl;
    cout << "Forest " << round++ << endl;
    Solve(trees);
  }
}
