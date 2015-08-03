#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

struct Rectangle {
  int llx;
  int lly;
  int urx;
  int ury;
};

void read_rectangle(const string& line, Rectangle* rec) {
  stringstream ss(line);
  ss >> rec->llx >> rec->lly >> rec->urx >> rec->ury;
}

// op
#define UPPER 1   // whole rectangle on top of y = n
#define LOWER 2
#define RIGHT 3
#define LEFT 4
bool satisfy(int op, const Rectangle& r, const Rectangle& o_r) {
  switch (op) {
    case UPPER:  // r upper than o_r
      return r.lly >= o_r.ury;
    case LOWER:
      return r.ury <= o_r.lly;
    case RIGHT:
      return r.llx >= o_r.urx;
    case LEFT:
      return r.urx <= o_r.llx;
    default:
      return false;
  }
}

// return true if point (x, y) in or on Rectangle r
bool in(int x, int y, const Rectangle& r) {
  return r.llx <= x && x <= r.urx && r.lly <= y && y <= r.ury;
}

void find_inners(
    const Rectangle& r, const Rectangle& o_r,
    vector<int>& xs, vector<int>& ys) {
  if (in(r.llx, r.lly, o_r)) {
    xs.push_back(r.llx);
    ys.push_back(r.lly);
  }
  if (in(r.llx, r.ury, o_r)) {
    xs.push_back(r.llx);
    ys.push_back(r.ury);
  }
  if (in(r.urx, r.lly, o_r)) {
    xs.push_back(r.urx);
    ys.push_back(r.lly);
  }
  if (in(r.urx, r.ury, o_r)) {
    xs.push_back(r.urx);
    ys.push_back(r.ury);
  }
}

bool diffside(int a1, int a2, int b) {
  return (b - a1) * (b - a2) < 0;
}

// x1 <= x2, y1 <= y2
bool intersect(int x1, int y1, int x2, int y2,
               const Rectangle& r,
               int& x, int& y) {
  if (y1 == y2 && r.lly < y1 && y1 < r.ury) {
    if (diffside(x1, x2, r.llx)) {
      x = r.llx; y = y1;
      return true;
    } else if (diffside(x1, x2, r.urx)) {
      x = r.urx; y = y1;
      return true;
    }
  } else if (x1 == x2 && r.llx < x1 && x1 < r.urx) {
    if (diffside(y1, y2, r.lly)) {
      x = x1; y = r.lly;
      return true;
    } else if (diffside(y1, y2, r.ury)) {
      x = x1; y = r.ury;
      return true;
    }
  }
  return false;
}

void find_intersects(const Rectangle& r, const Rectangle& o_r,
    vector<int>& xs, vector<int>& ys) {
  int x, y;
  // 1. horizonal edge
  if (intersect(r.llx, r.lly, r.urx, r.lly, o_r, x, y)) {
    xs.push_back(x);
    ys.push_back(y);
  }
  if (intersect(r.llx, r.ury, r.urx, r.ury, o_r, x, y)) {
    xs.push_back(x);
    ys.push_back(y);
  }
  // 2. vertical edge
  if (intersect(r.llx, r.lly, r.llx, r.ury, o_r, x, y)) {
    xs.push_back(x);
    ys.push_back(y);
  }
  if (intersect(r.urx, r.lly, r.urx, r.ury, o_r, x, y)) {
    xs.push_back(x);
    ys.push_back(y);
  }
}

void get_min_max(const vector<int>& vec, int& min, int& max) {
  min = 10000000; max = -1;
  for (int e : vec) {
    if (e < min) min = e;
    if (e > max) max = e;
  }
}

bool overlap(const Rectangle& r1, const Rectangle& r2, Rectangle& overlapped) {
  bool happen =
    satisfy(UPPER, r1, r2) || satisfy(UPPER, r2, r1) ||
    satisfy(LOWER, r1, r2) || satisfy(LOWER, r2, r1) ||
    satisfy(RIGHT, r1, r2) || satisfy(RIGHT, r2, r1) ||
    satisfy(LEFT,  r1, r2) || satisfy(LEFT,  r2, r1);
  if (happen) return false;

  vector<int> xs, ys;
  // 1. points in rectangle
  find_inners(r1, r2, xs, ys);
  find_inners(r2, r1, xs, ys);
  // 2. intersection points
  find_intersects(r1, r2, xs, ys);
  find_intersects(r2, r1, xs, ys);

  get_min_max(xs, overlapped.llx, overlapped.urx); 
  get_min_max(ys, overlapped.lly, overlapped.ury); 
  return true;
}

void dump(const Rectangle& r) {
  cout << r.llx << " " << r.lly << " " << r.urx << " " << r.ury << endl;
}

int main() {
  int round;
  cin >> round;
  string line;
  getline(cin, line);
  bool first = true;
  while (round-- > 0) {
    Rectangle r1, r2;
    getline(cin, line);  // blank line
    getline(cin, line);  // rectagnle #1
    read_rectangle(line, &r1);
    getline(cin, line);  // rectagnle #2
    read_rectangle(line, &r2);

    Rectangle overlapped;
    if (!first) {
      cout << endl;
    }
    first = false;
    if (overlap(r1, r2, overlapped)) {
      dump(overlapped);
    } else  {
      cout << "No Overlap" << endl;
    }
  }
}
