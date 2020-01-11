#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;

typedef vector<vector<LL>> MatLL;
typedef vector<LL> VecLL;

VecLL MatMul(const MatLL& m, const VecLL& v, LL M) {
  LL D = v.size();
  VecLL vr(D, 0);
  for (int i=0;i<D;++i) {
    for (int j=0;j<D;++j) {
      vr[i] += (m[i][j] * v[j]) % M;
      vr[i] %= M;
    }
  }
  return vr;
}

MatLL MatMul(const MatLL& m1, const MatLL& m2, LL M) {
  LL D = m1.size();
  MatLL mr(D, VecLL(D, 0));
  for (int i=0;i<D;++i) {
    for (int j=0;j<D;++j) {
      for (int k=0;k<D;++k) {
        mr[i][j] += (m1[i][k] * m2[k][j]) % M;
        mr[i][j] %= M;
      }
    }
  }
  return mr;
}

LL Solve(const VecLL& as, VecLL& fs, LL N, LL M) {
  LL D = as.size();

  if (N <= D) { return fs[N-1]; }

  LL power = N-D;
  // reverse fs: fd, fd-1, ...f1
  std::reverse(fs.begin(), fs.end());

  MatLL mat(D, VecLL(D, 0));
  // init mat 
  for (int i=0;i<D;++i) {
    mat[0][i] = as[i];
  }
  for (int i=1;i<D;++i) {
    mat[i][i-1] = 1;
  }
  
  while (power > 0) {
    if (power & 1) {
      fs = MatMul(mat, fs, M);
    }
    mat = MatMul(mat, mat, M);
    power = power >> 1;
  }
  return fs[0];
}

int main() {
  LL D, N, M;
  while (cin >> D >> N >> M) {
    if (D == 0 && N == 0 && M == 0) break;
    vector<LL> as(D, 0);
    for (int i=0;i<D;++i) {
      cin >> as[i];
      as[i] %= M;
    }
    vector<LL> fs(D, 0);
    for (int i=0;i<D;++i) {
      cin >> fs[i];
      fs[i] %= M;
    }
    cout << Solve(as, fs, N, M) << endl;
  }
}
