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
  int l, h, r;
  bool first = true;
  while (cin >> l >> h >> r) {
    while (!maxheap.empty() && maxheap.top().r < l) {
      // pop heap that should not exist
      Bldg top = maxheap.top();
      while (!maxheap.empty() && maxheap.top().r <= top.r) 
        maxheap.pop();  
      int rrr = maxheap.empty() ? 0 : maxheap.top().h;
      
      
      cout << " " << top.r << " " << rrr;
    }
    if (l < r) {
    if (maxheap.empty() || maxheap.top().h < h) {
      if (!first)
        cout << " ";
      else 
        first = false; 
      cout << l << " " << h;
    }
    maxheap.push(Bldg(h, r));
    }
  }

  // clear heap
  while (!maxheap.empty()) {
    Bldg top = maxheap.top();
    while (!maxheap.empty() && maxheap.top().r <= top.r)
      maxheap.pop();
    int rrr = maxheap.empty() ? 0 : maxheap.top().h;
      cout << " " << top.r << " " << rrr;
  }
  return 0;
}
