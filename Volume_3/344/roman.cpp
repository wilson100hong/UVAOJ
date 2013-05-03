#include <iostream>
using namespace std;
int I[101];
int V[101];
int X[101];
int L[101];
int C[101];

void roman(int n, int r);
void init() {
  for (int i = 0; i < 101; ++i) {
    I[i] = 0;
    V[i] = 0;
    X[i] = 0;
    L[i] = 0;
    C[i] = 0;
  }
  // todo 
  for (int i = 1; i < 101; ++i) 
    roman(i, i);
}

void roman(int n, int r) {
  if (r == 0) 
    return;

  if (r < 4) {
    I[n] += r;
  } else if (r == 4) {
    I[n] += 1;
    V[n] += 1;
  } else if (r < 9) {
    V[n] += 1;
    roman(n, r - 5);
  } else if (r == 9) {
    X[n] += 1;
    I[n] += 1;
  } else if (r < 40) {
    X[n] += (r / 10);
    roman(n, r % 10);
  } else if (r < 50) {
     L[n] += 1;
     X[n] += 1;
     roman(n, r - 40);
  } else if (r < 90) {
     L[n] += 1;
     roman(n, r - 50);
  } else if (r < 100) {
     C[n] += 1;
     X[n] += 1;
     roman(n, r - 90);
  } else if (r == 100) {
    C[n] += 1;
    roman(n, r - 100);
  }
}

int main () {
  init();
  int n;
  while (cin >> n) {
    if (n == 0)
      break;
    /*cout << n << ": " << I[n] <<"I" << V[n] <<"V" 
         << X[n] <<"X" << L[n] <<"L"
         << C[n] <<"C" <<  endl;
    */
    int ni = 0, nv = 0, nx = 0, nl = 0, nc = 0;
    for (int i = 1; i <= n; ++i) {
      ni += I[i];
      nv += V[i];
      nx += X[i];
      nl += L[i];
      nc += C[i];
    }
    cout << n << ": " 
         << ni << " i, "
         << nv << " v, "
         << nx << " x, "
         << nl << " l, "
         << nc << " c" << endl; 
  }
  return 0;  
}
