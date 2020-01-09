// 1. Overflow. Use boolean multiplication
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

typedef unsigned long long ULL;
typedef vector<vector<ULL>> Mat;
typedef vector<ULL> Vec;

void Dump(const Mat& m) {
  int N = m.size();
  for (int i=0;i<N;++i) {
    for (int j=0;j<N;++j) {
      cout << setw(3) << m[i][j];
    }
    cout << endl;
  }
}

void Dump(const Vec& v) {
  for (int i=0;i<v.size();++i) {
    cout << setw(3) << v[i];
  }
  cout << endl;
}

Vec MatMul(const Mat& m, const Vec& v) {
  const int N = m.size();
  Vec r(N, 0);
  for (int i=0;i<N;++i) {
    for (int j=0;j<N;++j) {
      r[i] |= (m[i][j] & v[j]);
    }
  }
  return r;
}

Mat MatMul(const Mat& m1, const Mat& m2) {
  const int N = m1.size();
  Mat mr(N, Vec(N, 0));

  for (int i=0;i<N;++i) {
    for (int j=0;j<N;++j) {
      for (int k=0;k<N;++k) {
        mr[i][j] |= (m1[i][k] & m2[k][j]);
      }
    }
  }
  return mr;
}

bool Solve(Mat mat, int S, int E, int D) {
  int N = mat.size();
  Vec v(N, 0);
  v[S] = 1;

  while (D) {
    if (D & 1) {
      v = MatMul(mat, v);
    }
    D = D >> 1;
    mat = MatMul(mat, mat);   // mat = mat^2;
  }
  
  return v[E] > 0;
}

int main() {
  int C, L;
  while (cin >> C >> L) {
    if (C == 0 && L == 0) break;

    Mat matrix(C, Vec(C, 0));
    for (int i=0;i<L;++i) {
      int A, B;
      cin >> A >> B;
      A--; B--;
      matrix[A][B] = matrix[B][A] = 1;
    }

    int S, E, D;
    cin >> S >> E >> D;
    S--; E--;
    if (Solve(matrix, S, E, D)) {
      cout << "Yes, Teobaldo can travel." << endl;
    } else {
      cout << "No, Teobaldo can not travel." << endl;
    }
  }
}

