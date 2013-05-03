#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Shape {
public:
  virtual bool in(double x, double y) = 0;
};

class Rect : public Shape{
public:
  double lx, ly, rx, ry;
  Rect(double lx_, double ly_, double rx_, double ry_) {
    if (lx_ > rx_) {
      double tmp = lx_;
      lx_ = rx_;
      rx_ = tmp;  
    }
    if (ry_ > ly_) {
      double tmp = ry_;
      ry_ = ly_;
      ly_ = tmp;
    }
    lx = lx_; ly = ly_; rx = rx_; ry = ry_;
  }

  bool in(double x, double y) {
    return lx < x && x < rx && ry < y && y < ly;
  }
}; 

class Circle: public Shape {
public:
  double cx, cy, r;
  Circle(double x_, double y_, double r_) {
    cx = x_; cy = y_; r = r_;
  }
  bool in(double x, double y) {
    return (cx - x)*(cx - x) + (cy - y)*(cy - y) < r*r;
  }
};

double abs(double n) {
  return n > 0 ? n : -n;
}
#define EP 10e-9

int main() {
  string line;
  vector<Shape*> shapes;
  while (getline(cin, line)) {
    if (line == "*")
      break;
    stringstream ss(line);
    // todo:
    string type;
    ss >> type;
    if (type == "r") {
      double lx, ly, rx, ry;
      ss >> lx >> ly >> rx >> ry;
      shapes.push_back(new Rect(lx, ly, rx, ry));    
    } else if (type == "c") {
      double cx, cy, r;
      ss >> cx >> cy >> r;
      shapes.push_back(new Circle(cx, cy, r));
    }
  }
  double x,y;
  int cnt = 1;
  while (cin >> x >> y) {
    if (abs(x - 9999.9) <= EP && abs(y - 9999.9) <= EP) 
      break;
    
    vector<int> contains;
    for (int i = 0; i < shapes.size(); ++i) {
      Shape* shape = shapes[i];
      if (shape->in(x, y))
        contains.push_back(i + 1);
    }
    if (contains.size() == 0)
      cout << "Point " << cnt << " is not contained in any figure" << endl;
    else {
      for (int j = 0; j < contains.size(); ++j)
        cout << "Point " << cnt << " is contained in figure " <<  contains[j] << endl;
    }
    cnt++;
  }
  
  return 0;
}
