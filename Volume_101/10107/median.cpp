#include <iostream>
#include <queue>
using namespace std;
int main() {
  priority_queue< int, vector<int>, less<int> > L;  // low part, max heap
  priority_queue< int, vector<int>, greater<int> > H;  // high part, min heap
  int med = -1, n;
  while (cin >> n) {
    // update heaps first
    if (n <= med) {
      L.push(n);
      if (L.size() - H.size() > 1) {
        int l = L.top();
        L.pop();
        H.push(l);
      }
    } else { 
      H.push(n);
      if (H.size() - L.size() > 1) {
        int h = H.top();
        H.pop();
        L.push(h);
       }
    }
    
       // get median
    if (L.size() == H.size())   // != 0
      med = (L.top() + H.top()) / 2;
    else if (L.size() < H.size())
      med = H.top();
    else
      med = L.top();
    cout << med << endl;
  
  }

  return 0;
}
