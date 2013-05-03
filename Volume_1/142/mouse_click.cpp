#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

struct Point{
  int x;
  int y;
};

struct Icon{
  Point p;
  bool visible;
};

struct Region{
  Point top_left;
  Point bottom_right;
};

int Dist(const Point& p1, const Point& p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool InRegion(const Region& r, const Point& p) {
  int lx = min(r.top_left.x, r.bottom_right.x);
  int rx = max(r.top_left.x, r.bottom_right.x);
  int by = min(r.top_left.y, r.bottom_right.y);
  int ty = max(r.top_left.y, r.bottom_right.y);
  return lx <= p.x && p.x <= rx && by <= p.y && p.y <= ty;
}

int main() {
  string line;
  vector<Icon> icons;
  vector<Region> regions;
  while (getline(cin, line)) {
    if (line == "#")
      break;
    stringstream ss(line);
    string cmd;
    ss >> cmd;
    if (cmd == "I") {
      Icon icon;
      ss >> icon.p.x >> icon.p.y;
      icon.visible = true;
      for (int i = 0; i < regions.size(); ++i) {
        if (InRegion(regions[i], icon.p)) {
          icon.visible = false;
          break;
        }
      }
      icons.push_back(icon);
    } else if (cmd == "R") {
      Region region;
      ss >> region.top_left.x >> region.top_left.y 
         >> region.bottom_right.x >> region.bottom_right.y;
      regions.push_back(region);
      for (int i = 0; i < icons.size(); ++i) {
        if (icons[i].visible && InRegion(region, icons[i].p))
          icons[i].visible = false;
      }
    } else if (cmd == "M") {
      Point click;
      ss >> click.x >> click.y;
      bool in_region = false;
      for (int i = regions.size() - 1; i >= 0; --i) {
        if (InRegion(regions[i], click)) {
          cout << (char) ( i + 'A') << endl;
          in_region = true;
          break;
        }
      }
      if (!in_region) {
        vector<int> selected;
        int min_dist = 1 << 30;
        for (int i = 0; i < icons.size(); ++i) {
          int dist = Dist(icons[i].p, click);
          if (icons[i].visible && dist <= min_dist) {
            if (dist < min_dist) {
              min_dist = dist;
              selected.clear();
            }
            selected.push_back(i + 1);
          }
        }
        for (int i = 0; i < selected.size(); ++i) {
          cout.width(3);
          cout << selected[i];
        }
        cout << endl;
      }
    }

  }

}
