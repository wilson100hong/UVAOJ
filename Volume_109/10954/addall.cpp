#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
bool compare(int a, int b) {
  return a > b;
}
int main() {
  int n;
  while (1) {
    cin >> n;
    if (n == 0) 
      break;
    priority_queue<int, vector<int>, function<bool(int, int)>> pq(compare);
    for (int i = 0; i < n; ++i) {
      int a;
      cin >> a;
      pq.push(a);
    }
    int cost = 0;
    while (pq.size() > 1) {
      int a = pq.top();
      pq.pop();
      int b = pq.top();
      pq.pop();
      int c = a + b;
      cost += c;
      pq.push(c);
    }
    cout << cost << endl;
  }
}
