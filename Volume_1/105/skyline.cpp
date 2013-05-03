#include <iostream>
#include <queue>
using namespace std;

class Bldg {
public:
  Bldg(int l_, int h_,  int r_) {
    l = l_;
    h = h_;
    r = r_;
  }
  int l;
  int r;
  int h;
  inline bool operator<(const Bldg& b) const {
    if (h != b.h)
      return h < b.h;
    else
      return r < b.r;
  }
};

bool first = true;

void dumpXY(int x, int y) {
  if (!first)
    cout << " ";
  else
    first = false;
  cout << x << " " << y;
}

int main() {
  priority_queue<Bldg> Lheap;
  priority_queue<Bldg> Rheap;
  int l, h, r;
  bool first = true;
  while (cin >> l >> h >> r) {
    if (l == r)
      continue;
    Bldg cur(l, h, r);
    if (!Lheap.empty() && l != Lheap.top().l)  {
      // Lheap is not empty 
      dumpXY(Lheap.top().l, Lheap.top().h);
      while(!Lheap.empty()) {
        Bldg Ltop = Lheap.top();
        Lheap.pop();
        Rheap.push(Ltop);
      }
    }
    while (!Rheap.empty() && Rheap.top().r < cur.l) {
      Bldg Rtop = Rheap.top();
      while (!Rheap.empty() && Rheap.top().r <= Rtop.r)
        Rheap.pop();
      dumpXY(Rtop.r, Rheap.empty() ? 0 : Rheap.top().h);
    }
    // TODO: handle == 
    if (Rheap.empty() || Rheap.top().h < cur.h) {
      Lheap.push(cur);
    } else {
      Rheap.push(cur);
    }
  }
  
  if (!Lheap.empty()) {
    dumpXY(Lheap.top().l, Lheap.top().h);
    while(!Lheap.empty()) {
      Bldg Ltop = Lheap.top();
      Lheap.pop();
      Rheap.push(Ltop);
    }
  }

  while (!Rheap.empty()) {
    Bldg Rtop = Rheap.top();
    while (!Rheap.empty() && Rheap.top().r <= Rtop.r)
      Rheap.pop();
    dumpXY(Rtop.r, Rheap.empty() ? 0 : Rheap.top().h);
  }
  cout << endl;
  return 0;
}
