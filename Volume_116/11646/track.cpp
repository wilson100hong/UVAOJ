#include <iostream>
#include <cmath>
#include <utility>
#include <iomanip>
using namespace std;

pair<double, double> solve(double a, double b) {
    double m = atan(b/a);
    double k = sqrt(1 + (b/a)*(b/a));
    double r = 100.0 / (m + cos(m));
    double length = 2*r*cos(m);
    double width = length * (b/a);
    return {length, width};
}

int main() {
    string line;
    int tcase = 1;
    while(getline(cin, line)) {
        int a = 0, b = 0;
        int ida = 0;
        // read length
        while (line[ida] != ' ') {
            a = a*10 + (line[ida] - '0');
            ida++;
        }
        ida += 3;  // skip " : "
        while (ida < line.size()) {
            b = b *10 + (line[ida] - '0');
            ida++;
        }

        pair<double, double> ans = solve(a, b);
        cout << fixed;
        cout << setprecision(10);
        cout << "Case " << tcase++ <<": " << ans.first << " " << ans.second << endl;
    }
}
