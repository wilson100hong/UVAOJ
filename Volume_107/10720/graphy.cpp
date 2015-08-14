// Havel Hakami algorithm
// https://en.wikipedia.org/wiki/Havel%E2%80%93Hakimi_algorithm
// WA#1 check element, each element should 0 < a < n
// WA#2 when loop "cur", only subtract "top" when it is > 0
#include <algorithm>
#include <iostream>
#include <queue>  // priority_queue
using namespace std;

void swap(priority_queue<int>*& a, priority_queue<int>*& b) {
  priority_queue<int>* c = a;
  a = b;
  b = c;
}

bool havel_hakami(const priority_queue<int>& heap) {
  priority_queue<int> q1 = heap, q2;
  priority_queue<int> *qptr = &q1, *tmp = &q2;
  if (heap.top() > heap.size()) {
    return false;
  }

  while (!qptr->empty()) {
    int top = qptr->top();
    qptr->pop();
    while (!qptr->empty()) {
      int cur = qptr->top();
      qptr->pop();
      if (top > 0) {
        cur--;
        top --;  // only subtract top when it still > 0
      }
      if (cur < 0) {  // should not happen
        return false;
      } else if (cur > 0) {
        tmp->push(cur);
      }
      // if cur == 0, discard it
    }
    if (top != 0)  {
      return false;
    }
    swap(qptr, tmp);
  }
  return qptr->empty();
}

using namespace std;
int main() {
  int n, a;
  while (1) {
    cin >> n;
    if (n == 0)
      break;
    priority_queue<int> heap;
    bool possible = true;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
      cin >> a;
      if (a > n || a < 0) {
        possible = false;
      }
      sum += a;
      heap.push(a);
    }
    if (!possible || sum % 2 != 0) {
      cout << "Not possible" << endl;
    } else {
      cout << (havel_hakami(heap) ? "Possible" : "Not possible") << endl;
    }
  }
}
