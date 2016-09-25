// 2016/09/25
// STARS  : ****
// SKILLS : dp, maximum sum with span limit
//
// 1. 4x the matrix to avoid annoying wrap
// 2. this is finding maximum sum of submatrix like in UV 108
// 3. size of submatrix is limited! use deque. NOTE the deque
//    maintaining.
// Trap: result can be < 0

#include <iostream>
#include <cstring>
#include <deque>
#include <vector>
#include <limits>
using namespace std;

int max(int a, int b) {
  return a > b ? a : b;
}

// maximum sum sequence at most span
int max_seq_range(const vector<int>& seq, int span) {
  int n = seq.size();

  vector<int> sum(n, 0);
  sum[0] = seq[0];
  for (int i=1;i<n;++i) {
    sum[i] = sum[i-1] + seq[i];
  }

  deque<int> pipe;
  int best = sum[0];
  pipe.push_back(0);
  for (int i=1;i<n;++i) {
    int cur = sum[i] - sum[pipe.front()];
    if (cur > best) {
      best = cur;
    }
    // add sum[i] to pipe
    while (!pipe.empty() && sum[pipe.back()] > sum[i]) {
      pipe.pop_back();
    }
    pipe.push_back(i);

    // pop sum[i] until in span ragne
    int sh = i-span+1;
    while (pipe.front() < sh) {
      pipe.pop_front();
    }
  }
  return best;
}

typedef vector<vector<int>> Torus;
int solve(const Torus& torus, int span) {
  // NOTE! ans should initailzed to min int
  int ans = numeric_limits<int>::min();

  int n = torus.size();
  for (int i=0;i<n-span;++i) {
    vector<int> sum(n, 0);
    for (int j=i;j<i+span;++j) {
      for (int k=0;k<n;++k) {
        sum[k] += torus[j][k];
      }
      ans = max(ans, max_seq_range(sum, span));
    }
  }
  return ans;
}

int main() {
  int cases;
  cin >> cases;
  while (cases--) {
    int N;
    cin >> N;
    Torus torus(2*N, vector<int>(2*N, 0));
    for (int i=0;i<N;++i) {
      for (int j=0;j<N;++j) {
        cin >> torus[i][j];
        torus[i][N+j] = torus[N+i][j] = torus[N+i][N+j] = torus[i][j];
      }
    }
    cout << solve(torus, N) << endl;
  }
}
