#include <iostream>
#include <queue>
using namespace std;

void bubblesort(int* ary, int n) {
  for (int i = n - 1; i >=0; --i) {
    for (int j = 0; j < i; ++j) {
      if (ary[j] > ary[j + 1]) {
        int tmp = ary[j];
        ary[j] = ary[j + 1];
        ary[j + 1] = tmp;
      }
    }
  }
}

void dump(int* ary, int n) {
  for (int i = 0; i < n; ++i)
    cout << ary[i] << ", ";
  cout << endl;
}
// does a contains b?
bool wraps(int* a, int* b, int n) {
  for (int i = 0; i < n; ++i) {
    if (a[i] <= b[i])
      return false;
  }
  return true;
}

int main() {
  int num, dim;
  while (cin >> num >> dim) {
    //cout << num << dim << endl;
    int** measures = new int*[num];
    bool** edges = new bool*[num];
    bool* roots = new bool[num];
    int* steps = new int[num];
    int* parents = new int[num];

    for (int i = 0; i < num; ++i) {
      parents[i] = -1;
      roots[i] = true;
      steps[i] = 0;
      measures[i] = new int[dim];
      edges[i] = new bool[num];
      for (int j = 0; j < dim; ++j) {
        cin >> measures[i][j];
      }
      for (int j = 0; j < num; ++j) {
        edges[i][j] = false;
      }
      bubblesort(measures[i], dim);
      // dump(measures[i], dim);
      for (int j = 0; j < i; ++j) {
        if (wraps(measures[i], measures[j], dim))  {
          edges[i][j] = true;
          roots[j] = false;
        } else if (wraps(measures[j], measures[i], dim)) {
          edges[j][i] = true;
          roots[i] = false;
        }
      }
    }
    /*
    cout << "Edges constructed." << endl;
    for (int i = 0; i < num; ++i) {
      for (int j = 0; j < num; ++j)
        cout << edges[i][j] << ",";
      cout << endl;
    }
    */
    for (int i = 0; i < num; ++i) {
      if(roots[i]) {
        // BFS 
        queue<int> myqueue;
        steps[i] = 1;
        myqueue.push(i);
       
        while (!myqueue.empty()) {
          int from = myqueue.front();
          int curstep = steps[from] + 1;
          myqueue.pop();
          for (int to = 0; to < num; to++) {
            if (edges[from][to] && curstep > steps[to]) {
              steps[to] = curstep;
              parents[to] = from;
              myqueue.push(to);
            }
          }
        }
      }
    }
    //cout << "BFS completed" << endl;
    // fix max
    int maxlen = -1, maxend = -1;
    for (int i = 0; i < num; ++i) {
       if (steps[i] > maxlen) {
          maxlen = steps[i];
          maxend = i;
       }
    }
    cout << maxlen << endl;
    cout << maxend + 1;
    maxend = parents[maxend];
    while (maxend != -1) {
      cout << " " << maxend + 1;
      maxend = parents[maxend];
    }
    cout << endl;
    for (int i = 0; i < num; ++i) {
      delete measures[i];
      delete edges[i];
    }
    delete measures;
    delete edges;
    delete roots;
    delete steps;
  }
  
  return 0;
}
