// NOTE: precision fraction
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>  // std::min
using namespace std;

#define EPS 1e-5
double solve(double x, double y, double c) {
    // solve 
    double ic = 1.0/c;
    double l = 0, r = min(x, y);
    while (r - l > EPS) {
        double d = (l+r)/2.0;
        double a = sqrt(x*x - d*d);
        double b = sqrt(y*y - d*d);

        double is = (1.0/a + 1.0/b);
        if (is == ic) {
            return d;
        } else if (is > ic) { 
            r = d;
        } else{
            l = d;
        }
    }
    return l;
}

int main() {
    string line;
    while(getline(cin, line)) {
        stringstream ss(line);
        double x, y, c;
        ss >> x >> y >> c;
        double ans = solve(x, y, c);

        cout << fixed;
        //cout << setprecision(3) << ans + 0.0005 << endl;
        cout << setprecision(3) << ans  << endl;
    }
}
