#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ull;
int MONTH[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

ull Y400 = 400*365 + 100 - 4 + 1;

bool leap_year(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return y%4 == 0;
}

int month_days(int y, int m) {
    if (m != 2) return MONTH[m];
    if (leap_year(y)) return 29;
    else return 28;
}

int main() {
    ull N, D, M, Y;
    while (cin >> N >> D >> M >> Y) {
        if (N==0&&D==0&&M==0&&Y==0) break;
        // 400 years
        Y += (N/Y400) * 400;
        N %= Y400;

        // at most 399 times
        while (N >= 365) {
            // BUG
            if (!leap_year(Y)) {
                Y++;
                if (leap_year(Y) && M >= 3) {
                    D--;
                    if (D == 0) {
                        M--;
                        D = month_days(Y, M);
                    }
                }
            } else {  // leap year
                if (M == 1 && D == 1) {
                    M = 12;
                    D = 31;
                } else {  
                    Y++;
                    if (M < 3) {
                        D--;
                        if (D == 0) {
                            M--;
                            D = month_days(Y, M);
                        }
                    }
                }
            }
            N -= 365;
        }

        // N < 365
        while (month_days(Y, M) - D < N) {
            N -= (month_days(Y, M) - D + 1);
            M++;
            D = 1;
            if (M == 13) {
                M = 1;
                Y++;
            }
        }
        D += N;

        cout << D << " " << M << " " << Y << endl;

    }

}
