#include <iostream>
#include <queue>
using namespace std;

class Bldg {
public:
  Bldg(int h_,  int r_) {
    h = h_;
    r = r_;
  }
  int r;
  int h;
  
  inline bool operator<(const Bldg& b) const {
    if (h != b.h)
      return h < b.h;
    else
      return r < b.r;
  }
};

int main() {
  priority_queue<Bldg> maxheap;
  priority_queue<Bldg> tmpheap;
  int l, h, r;
  bool first = true;
  int tl = -1;
  while (cin >> l >> h >> r) {
    if (tl != -1 && l > tl) {
      // clear max heap
      while (!maxheap.empty() && maxheap.top().r < tl) {
        Bldg top = maxheap.top();
        while (!maxheap.empty() && maxheap.top().r <= top.r) 
          maxheap.pop();  
        int rrr = maxheap.empty() ? 0 : maxheap.top().h;
        cout << " " << top.r << " " << rrr;
      }
      // tmp heap should can be null!     
      if (!tmpheap.empty()) {
        Bldg tb = tmpheap.top();
        if (maxheap.empty() || maxheap.top().h < tb.h) {
          if (!first)
            cout << " ";
          else
            first = false;
          cout << tl << " " << tb.h;
        }
        while(!tmpheap.empty()) {
          maxheap.push(tmpheap.top());
          tmpheap.pop();
        }
      }
    }
    if (l < r)
      tmpheap.push(Bldg(h, r));
    tl = l;
  }
 
  // clear tmp heap
  if (!tmpheap.empty()) {
    Bldg tb = tmpheap.top();
    if (maxheap.empty() || maxheap.top().h < tb.h) {
      if (!first)
        cout << " ";
      else
        first = false;
      cout << tl << " " << tb.h;
    }
    while(!tmpheap.empty()) {
      maxheap.push(tmpheap.top());
      tmpheap.pop();
    }
  }
  
  // clear max heap
  while (!maxheap.empty()) {
    Bldg top = maxheap.top();
    while (!maxheap.empty() && maxheap.top().r <= top.r)
      maxheap.pop();
    int rrr = maxheap.empty() ? 0 : maxheap.top().h;
    if (!first)
      cout << " ";
    else 
      first = false;
    cout << top.r << " " << rrr;
  }
  return 0;
}
