#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <cstring>
#include <limits>
#include <queue>
using namespace std;

// 2016/10/20
// STAR:
// SKILL: bfs
// TRAP: memset

struct Point {
  int x;
  int y;
};

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) { 
  return a > b ? a : b;
}

vector<Point> extend(const vector<Point>& points) {
  // don't worry about duplicate points.
  vector<Point> res;
  int n = points.size();
  for (int i=0;i<n;++i) {
    int j=(i+n-1)%n;
    if (points[i].x == points[j].x) {
      int min_y = min(points[i].y, points[j].y);
      int max_y = max(points[i].y, points[j].y);
      for (int y=min_y; y<=max_y; ++y) {
        res.push_back({points[i].x, y});
      }
    } else if (points[i].y == points[j].y) {
      int min_x = min(points[i].x, points[j].x);
      int max_x = max(points[i].x, points[j].x);
      for (int x=min_x; x<=max_x; ++x) {
        res.push_back({x, points[i].y});
      }
    } else {
      cout << "WILSON STUPID!" << endl;
    }
  }
  return res;
}


struct State {
  int dist;
  Point point;
};

#define MAX_SIZE  2005
int CITY[MAX_SIZE][MAX_SIZE];

int DY[] = {1,-1,0,0};
int DX[] = {0,0,-1,1};

#define MALL2 -1

int solve(const vector<Point>& mall1, const vector<Point>& mall2) {
  // 0: unvisit
  memset(CITY, 0, sizeof(int)*MAX_SIZE*MAX_SIZE);
  for (const Point& p : mall2) {
    CITY[p.y][p.x] = MALL2;
  }

  queue<State> que;
  for (const Point& p : mall1) {
    if (CITY[p.y][p.x] == MALL2) {
      return 0;
    }
    CITY[p.y][p.x] = 1; // MALL1, start from 1
    que.push({1, p});
  }

  // BFS
  while (!que.empty()) {
    State head = que.front();
    que.pop();
    Point p = head.point;
    for (int d=0;d<4;++d) {
      int nx = p.x + DX[d];
      int ny = p.y + DY[d];
      if (0<=nx && nx<MAX_SIZE && 0<=ny && ny<MAX_SIZE) {
        if (CITY[ny][nx] == MALL2) {
          return head.dist;
        } else if (CITY[ny][nx] == 0) {
          CITY[ny][nx] = head.dist+1;
          que.push({CITY[ny][nx], {nx, ny}});
        }
      }
    }
  }
  return -1;  // should never happen
}

int main() {
  int n1, n2;
  while (cin >> n1) {
    if (n1==0) break;
    // 1. read mall1
    Point point;
    vector<Point> pts;
    for (int i=0;i<n1;++i) {
      // avenue, street
      cin >> point.x >> point.y;
      pts.push_back(point);
    }
    vector<Point> mall1 = extend(pts);
    
    // 2. read mall2
    cin >> n2;
    pts.clear();
    for (int i=0;i<n2;++i) {
      // avenue, street
      cin >> point.x >> point.y;
      pts.push_back(point);
    }
    vector<Point> mall2 = extend(pts);
    cout << solve(mall1, mall2) << endl;
  }
}
