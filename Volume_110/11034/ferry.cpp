#include <iostream>
#include <queue>
using namespace std;
int main() {
  int round;
  cin >> round;
  while (round-- > 0) {
    int l, m;
    cin >> l >> m;
    l *= 100;  // m -> cm
    queue<int> lq, rq;

    for (int i = 0; i < m; ++i) {
      int cm; 
      string side;
      cin >> cm >> side;
      if (side == "left") {
        lq.push(cm);
      } else if (side == "right") {
        rq.push(cm);
      }
    }
    bool left = true;
    int cross = 0;
    while (!lq.empty() || !rq.empty()) {
      queue<int>* q = left ? &lq : &rq;
      int sum = 0;
      while (!q->empty() && sum + q->front() <= l) {
        sum += q->front();
        q->pop();
      }
      left = !left;
      cross++;
    }
    cout << cross << endl;
  }
}
