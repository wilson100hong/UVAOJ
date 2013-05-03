#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Tree{
  double x;
  double y;
  double z;
  double min_dist2;
};

#define MAX 1<<30
#define EPS 1e-8
bool is0(double d) {
  return abs(d) < EPS;
}
int main() {
  double x, y, z;
  vector<Tree> forest;
  while (cin >> x >> y >> z) {
    if (is0(x) && is0(y) && is0(z))
      break;
    Tree tree;
    tree.x = x; tree.y = y; tree.z = z;
    tree.min_dist2 = MAX; 
    forest.push_back(tree);
  }
  int n = forest.size();
  for (int i=0;i<n;++i) {
    for (int j=i+1;j<n;++j) {
      double dist2 = (forest[i].x - forest[j].x)* (forest[i].x - forest[j].x);
      dist2 += (forest[i].y - forest[j].y)* (forest[i].y - forest[j].y);
      dist2 += (forest[i].z - forest[j].z)* (forest[i].z - forest[j].z);
      if (dist2 < forest[i].min_dist2) 
        forest[i].min_dist2 = dist2;
      if (dist2 < forest[j].min_dist2) 
        forest[j].min_dist2 = dist2;
    }
  }
  int bin[10] = {0,0,0,0,0, 0,0,0,0,0};
  for (int i=0;i<n;++i) {
    // TODO: might have bug
    int sq = (int)sqrt(forest[i].min_dist2);
    if (sq < 10)
      bin[sq]++;
  }
  for (int i=0;i<10;++i) {
    cout.width(4);
    cout << bin[i];
  }
  cout << endl;
}
