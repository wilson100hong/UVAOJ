#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
class Rect{
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
    lx = lx_;
    ly = ly_;
    rx = rx_;
    ry = ry_;
  }

  bool in(double x, double y) {
    return lx < x && x < rx && ry < y && y < ly;
  }
}; 

double abs(double n) {
  return n > 0 ? n : -n;
}
#define EP 10e-9
int main() {
  string line;
  vector<Rect> rects;
  while (getline(cin, line)) {
    if (line == "*")
      break;
    stringstream ss(line);
    string r;
    ss >> r;
    double lx, ly, rx, ry;
    ss >> lx >> ly >> rx >> ry;
    rects.push_back(Rect(lx, ly, rx, ry));    
  }
  double x,y;
  int cnt = 1;
  while (cin >> x >> y) {
    if (abs(x - 9999.9) <= EP && abs(y - 9999.9) <= EP) 
      break;
    
    vector<int> contains;
    for (int i = 0; i < rects.size(); ++i) {
      Rect rect = rects[i];
      if (rect.in(x, y))
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
