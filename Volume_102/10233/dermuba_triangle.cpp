#include <iostream>
#include <cmath>
#include <utility>
#include <iomanip>
using namespace std;

typedef unsigned long long ULL;
typedef pair<int, int> II;
typedef pair<double, double> DD;

double kSR3 = sqrt(3.0);

II GetRC(ULL n) {
  ULL t = sqrt(n+1);
  if (t*t < n+1) {
    t++;
  }
  
  int r = t - 1;
  int c = n - r*r - r;
  return {r, c};
}

DD GetPos(const II& rc) {
  int r = rc.first, c = rc.second;

  double x = 0.5 * c;
  double y = -1 * 0.5*kSR3 * r;

  if ((r%2==0 && abs(c)%2==0) ||
      (r%2==1 && abs(c)%2==1)) {
    y -= kSR3 / 3.0;
  } else {
    y -= kSR3 / 6.0;
  }

  return {x, y};
}

double Solve(const DD& pos0, const DD& pos1) {
  return hypot(pos0.first - pos1.first, pos0.second - pos1.second);
}

int main() {
  int N, M;
  while (cin >> N >> M) {
    auto pos0 = GetPos(GetRC(N));
    auto pos1 = GetPos(GetRC(M)); 
    
    double dist = Solve(pos0, pos1);
    cout << fixed << setprecision(3) << dist << endl;
  }
}
