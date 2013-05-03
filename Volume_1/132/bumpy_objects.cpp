#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point{
  int index;
  int x;
  int y;
};

// Positive if CCW,
// 0 if common line
// Negative if CW
int cross(const Point& o, const Point& a, const Point& b) {
  return (a.x - o.x) * (b.y - o.y) - (b.x - o.x) * (a.y - o.y);
}

int dot(const Point& o, const Point& a, const Point& b) {
  return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

int ComparePoint(const Point& a, const Point& b) {
  if (a.x == b.x)
    return a.y < b.y;
  else
    return a.x < b.x;
}

Point PickCandidate(const Point& a, const Point& b) {
  if (a.index > b.index)
    return a;
  else
    return b;
}

// NOTE: the last point of the result is the first point
vector<Point> ConvexHull(vector<Point>& pts) {
  int k = 0, n = pts.size();
  vector<Point> ch(2 * n);
  sort(pts.begin(), pts.end(), ComparePoint);
  // Lower part
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross(ch[k - 2], ch[k - 1], pts[i]) < 0) {
      k--;
    }
    ch[k++] = pts[i];
  }
  // Upper part
  for (int i = n - 2, t = k + 1; i >= 0; --i) {
    while (k >= t && cross(ch[k - 2], ch[k - 1], pts[i]) < 0) {
      k--;
    }
    ch[k++] = pts[i];
  }
  ch.resize(k);
  return ch;
}

bool LiesIn(const Point& p, const Point& p1, const Point& p2) {
  // true if p lies in p1 - p2 extend region
  return dot(p1, p, p2) >= 0 && dot(p2, p, p1) >= 0;
}

void Padding(string s, int pad) {
  cout << s;
  int len = s.length();
  for (int i= 0; i < pad - len; ++i)
    cout << " ";
}

#define INF 1 << 25 
int main() {
  string name;
  Point center, p;
  vector<Point> pts;
  while (cin >> name) {
    if (name == "#")
      break;
    cin >> center.x >> center.y;
    int index = 1;
    pts.clear();
    while (cin >> p.x >> p.y) {
      p.index = index++;
      if (p.x == 0 && p.y == 0)
        break;
      pts.push_back(p);
    }
    vector<Point> ch = ConvexHull(pts);
    int best = INF;
    int j = 0, n = ch.size();
    while (j < n - 1) {
      // Find next point common line with j, j + 1, ...
      int next = j + 1;
      while (next + 1 < n && cross(ch[j], ch[next], ch[next + 1]) == 0)
        next++;
      if (LiesIn(center, ch[j], ch[next])) {
        int score = ch[j].index;
        for (int i = j; i <= next; ++i)
          if (ch[i].index > score)
            score = ch[i].index;
        best = min(best, score);
      }
      j = next;
    }

    Padding(name, 20);
    cout << best << endl;
  }
}
