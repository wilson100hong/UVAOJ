// NOTE: brute force O(N^2) won't work. You have to use merge sort O(NlogN)
#include <iostream>
#include <vector>
using namespace std;

int merge_sort(vector<int>& list, int l, int r) {
  // cout << "L:" << l << "  R:" << r << endl;
  if (l==r) {
    return 0;
  }
  int pivot = (l+r)/2;
  int m1 = merge_sort(list, l, pivot);
  int m2 = merge_sort(list, pivot+1, r);

  vector<int> merged;
  int i=l, j=pivot+1, m=0;
  while (i<=pivot && j<=r) {
    if (list[i] < list[j]) {
      merged.push_back(list[i]);
      i++;
    } else if (list[i] > list[j]) {
      merged.push_back(list[j]);
      j++;
      m += (pivot-i+1);  // Tricky!
    } else {
      cout << "YOU IDIOT" << endl;
    }
  }

  while (j<=r) {
    merged.push_back(list[j]);
    j++;
  }
  while (i<=pivot) {
    merged.push_back(list[i]);
    i++;
  }

  for (int k=l;k<=r;++k) {
    list[k] = merged[k-l];
  }
  return m1+m2+m;
}

int main() {
  int n;
  vector<int> list;
  while (cin >> n) {
    if (n == 0) break;
    list.clear();
    for (int i=0; i<n; ++i) {
      int x;
      cin >> x;
      list.push_back(x);
    }
    int steps = merge_sort(list, 0, list.size()-1);
    if (steps % 2 == 0) {
      cout << "Carlos" << endl;
    } else {
      cout << "Marcelo" << endl;
    }
  }
}
