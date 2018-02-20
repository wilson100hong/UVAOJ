#include <iostream>
#include <cmath>
#include <utility>
#include <tuple>
#include <iomanip>
using namespace std;

#define PI 2*acos(0)
//#define PI 3.14159265

// return R^2, r^2
pair<double, double> solve(int n, double A) {
    double a = A / n;
    double theta = PI / n;
    double R2 = a/(cos(theta)*sin(theta));
    double r2 = R2 * cos(theta)*cos(theta);
    return make_pair(R2, r2);
}

int main() {
    int n, t = 1;
    double A, r2, R2;
    while (cin >> n >> A) {
        if (n<3) break;

        tie(R2, r2) = solve(n, A);
        
        double official = A - PI*r2;
        double spectator = PI*R2 - A;

        cout << "Case " << t++ << ": ";
        cout << setprecision(5);
        cout << fixed << spectator << " " << official << endl;
    }
}
