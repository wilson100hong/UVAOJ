// 2016/10/02
// STAR: **
// SKILL: binary search, tie break
// 
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
using namespace std;

typedef unsigned long long int ULL;

pair<bool, vector<int>> dispatch(const vector<int>& books, int people, int cap) {
  // from end to head
  vector<int> partition(people, 0);
  int p = people - 1, b = books.size() - 1;
  int cnt = 0, loading = 0;
  while (p >= 0 && b >= 0) {
    if (loading + books[b] <= cap && b >= p) {
      loading += books[b];
      cnt++;
      b--;
    } else if (cnt > 0 && b+1 >= p) {
      partition[p] = cnt;
      loading = 0;
      cnt = 0;
      p--;
    } else {
      // cannot achieve
      break;
    }
  }

  if (b < 0) {
    partition[0] = cnt;
    return {true, partition};
  } else {
    return {false, partition};
  }
}


void solve(const vector<int>& books, int people) {
  ULL sum = 0;
  for (int b : books) {
    sum += b;
  }
  ULL avg = sum / people;  // floor
  ULL left = avg, right = sum;  // TODO: can optmize right
  // binary search
  bool ok;
  vector<int> partition;
  vector<int> best;
  while (left <= right) {
    ULL mid = (left + right) / 2;
    tie(ok, partition) = dispatch(books, people, mid);
    if (ok) {
      right = mid - 1;
      best = partition;
    } else {
      left = mid + 1;
    }
  }
  // print partition
  int cur = 0;
  for (int i=0;i<best.size();++i) {
    if (i!= 0) {
      cout << " /";
    }
    for (int j=1;j<=best[i];++j) {
      if (cur != 0) {
        cout << " ";
      }
      cout << books[cur++];
    }
  }
  cout << endl;
}


int main() {
  int cases;
  cin >> cases;
  while (cases--) {
    int M, K;
    cin >> M >> K;
    vector<int> books(M, 0);
    for (int i=0;i<M;++i) {
      cin >> books[i];
    }
    solve(books, K);
  }
}
