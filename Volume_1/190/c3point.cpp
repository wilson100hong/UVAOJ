#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

#define EPS 1e-8
typedef vector<double> vec;
typedef vector<vec> matrix;

// solve a square matrix
vec gauss_jordan(const matrix& A, const vec& b) {
  int n = A.size();
  matrix B(n, vec(n + 1));
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j)
      B[i][j] = A[i][j]; 
  for (int i = 0; i < n; ++i)
    B[i][n] = b[i];
  
  for (int i = 0; i < n; ++i) {
    int pivot = i;
    for (int j = i + 1; j < n; ++j) {
      if (abs(B[j][i]) > abs(B[pivot][i]))
        pivot = j;
    }
    swap(B[i], B[pivot]);
     
    if (abs(B[i][i]) < EPS)
      return vec(); 
      
    for (int j = i + 1; j <= n; ++j)
      B[i][j] /= B[i][i];
    
    for (int j = 0; j < n; ++j) {
      if (j != i) {

        for (int k = i + 1; k <= n; ++k) 
          B[j][k] -= B[j][i] * B[i][k];  
      }
    }
  }
  
  vec x(n);
  for (int i = 0; i < n; ++i)
    x[i] = B[i][n];
  return x;
}

void formatout(double f) {
  if (f < 0)
    cout << " - " << fixed << setprecision(3) << abs(f);
  else
    cout << " + " << fixed << setprecision(3) << abs(f);
}

int main() {
  double x, y;
  int n = 0;
  vec b(3);
  matrix mat(3, vec(3));

  while (cin >> x >> y) {
    mat[n][0] = x;
    mat[n][1] = y;
    mat[n][2] = 1;
    b[n] = - x*x - y*y;
    n++;
    if (n == 3) {
      vec answer = gauss_jordan(mat, b);
     double h = - answer[0] / 2.f;
      double k = - answer[1] / 2.f;
      double r2 = (mat[0][0]-h)*(mat[0][0]-h) + (mat[0][1]-k)*(mat[0][1]-k);
      cout << "(x";
      formatout(-h);
      cout << ")^2 + (y";    
      formatout(-k);
      cout << ")^2 = ";
      cout << sqrt(r2) << "^2" << endl;
      
      cout << "x^2 + y^2";
      formatout(answer[0]);
      cout << "x";
      formatout(answer[1]);
      cout << "y";
      formatout(answer[2]);
      cout << " = 0" << endl << endl;
      
      n = 0; 
    }
  }
}
