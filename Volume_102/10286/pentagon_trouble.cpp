#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#define PI acos(-1.0)

int main() {
    double d;
    while (cin >> d) {
        cout.precision(10);
        cout << fixed;
        cout << d * (sin(PI*108.0/180) / sin(PI*63.0/180)) << endl;
        
    }
}
