// 2016/09/25
// STARS: *
// SKILLS: dp
//
// trap: every person can take only one object of each kind

#include <iostream>
#include <vector>
using namespace std;

struct Object {
  int w;  // weight
  int p;  // price
};

int max(int a, int b) {
  return a > b ? a : b;
}

int solve(const vector<Object>& objects, 
          const vector<int>& group,
          int max_w) {
  
  vector<int> dp1(max_w+1, 0);
  vector<int> dp2(max_w+1, 0);

  vector<int>* dp = &dp1;
  vector<int>* ndp = &dp2;

  for (int w=0;w<=max_w;++w) {
    dp->at(w) = (w >= objects[0].w ? objects[0].p : 0);
  }
  for (int i=1;i<objects.size();++i) {
    for (int w=0;w<=max_w;++w) {
      ndp->at(w) = dp->at(w);
      if (w - objects[i].w >= 0) {
        if (dp->at(w-objects[i].w) + objects[i].p > ndp->at(w)) {
          ndp->at(w) = dp->at(w-objects[i].w) + objects[i].p;
        }
      }
    }
    // swap tmp and dp
    vector<int>* tmp = dp;
    dp = ndp;
    ndp = tmp;
  }

  int sum = 0;
  for (int g : group) {
    sum += dp->at(g);
  }
  return sum;
}

int main() {
  int cases;
  cin >> cases;
  while (cases--) {
    int N, G;
    cin >> N;
    vector<Object> objects;
    for (int i=0;i<N;++i) {
      int p, w;
      cin >> p >> w;
      objects.push_back({w, p});
    }
    cin >> G;
    vector<int> group;
    int max_w = 0;
    for (int i=0;i<G;++i) {
      int w;
      cin >> w; 
      if (w > max_w) {
        max_w = w;
      }
      group.push_back(w);
    }
    cout << solve(objects, group, max_w) << endl;
  }
}
