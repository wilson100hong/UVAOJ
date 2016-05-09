#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>
using namespace std;

const double PI = 3.1415926535897;

void Solve(double a, double b, double c) {
    // Law of contangents
    // https://en.wikipedia.org/wiki/Law_of_cotangents
    double s = (a+b+c)/2.0;
    double r = sqrt((s-a)*(s-b)*(s-c)/s);
    double roses = PI*r*r;
    double violets = r*s-roses;
    // Basic trigonometrics
    double cosA = (b*b+c*c-a*a)/(2.0*b*c);
    double sinA = sqrt(1-cosA*cosA);
    // Big circum circle
    double R = a/(2.0*sinA);
    double sunfolowers = PI*R*R-r*s;
    cout << std::fixed;
    cout << std::setprecision(4);
    cout << sunfolowers << " " << violets << " " << roses << endl;
}

int main() {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        int a, b, c;
        ss >> a >> b >> c;
        Solve(a, b, c);
    }

}
