#include <iostream>
using namespace std;

struct Point{
  int x;
  int y;
};


// Does p contains in square at center with size?
bool contain(const Point& p, const Point& center, int size) {
  return center.x-size <= p.x && p.x <= center.x+size
      && center.y-size <= p.y && p.y <= center.y+size;
}

int rec_square(const Point& p, const Point& center, int size) {
  //cout << "size" << size << endl;
  if (size == 0)
    return 0;
  if (!contain(p, center, 2*size))
    return 0;
  int cur = contain(p, center, size) ? 1 : 0;
  if (p.x == center.x || p.y == center.y)
    return cur;
  else {
    int dx = p.x > center.x ? size : -1* size;
    int dy = p.y > center.y ? size : -1* size;
    Point nc;
    nc.x = center.x + dx; nc.y = center.y + dy;
    return cur + rec_square(p, nc, size/2); 
  }
}

int main() {
  int x, y, size;
  while (cin >> size >> x >> y) {
    if (x == y && y == size && size == 0)
      break;
    Point p;
    p.x = x; p.y = y;
    Point center;
    center.x = 1024; center.y = 1024;
    cout.width(3);
    cout << rec_square(p, center, size) << endl;
  }
}
