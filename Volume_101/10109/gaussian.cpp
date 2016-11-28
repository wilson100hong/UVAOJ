#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

// 2016/11/26
// STAR: **
// SKILL: Gaussian-Jordan, fracton arithematics
// TRAP: 1) overflow!

typedef long long LL;

LL myabs(LL a) {
    return a < 0 ? -a : a;
}

LL gcd(LL a, LL b) {
    a = myabs(a);
    b = myabs(b);
    if (a < b) return gcd(b, a);
    if (b == 0) return 1;
    if (a % b == 0) {
        return b;
    } else {
        return gcd(b, a % b);
    }
}

// represent lowest fraction n / d 
// 0/x will be reduce to 0/1
class Fraction {
  public:
    LL n;
    LL d;

    void reduce() {
        if (n==0) {
            d = 1;
        } else {
            bool neg = (n<0 && d>0) || (n>0 && d<0);
            LL g = gcd(n, d);
            n /= g; d /= g;
            d = myabs(d);
            n = neg ? -myabs(n) : myabs(n);
        }
    }

    Fraction(const string& str) {
        int cur = 0;
        while (str[cur] != '/' && cur < str.size()) {
            cur++;
        }
        if (cur == str.size()) {
            n = stoll(str);
            d = 1;
        } else {
            n = stoll(str.substr(0, cur));
            d = stoll(str.substr(cur+1));
        }
        reduce();
    }

    Fraction(LL on, LL od=1) : n(on), d(od) {
        reduce();
    }

    string str() {
        string res = to_string(n);
        if (d != 1) {
            res +=  "/" + to_string(d);
        }
        return res;
    }

	Fraction& operator=(const Fraction& other) {
        n = other.n;
        d = other.d;
        reduce();
		return *this;
	}

    Fraction& operator+=(const Fraction& rhs) {
        n = n*rhs.d + d*rhs.n;
        d *= rhs.d;
        reduce();
        return *this;
    }

    Fraction& operator-=(const Fraction& rhs) {
        n = n*rhs.d - d*rhs.n;
        d *= rhs.d;
        reduce();
        return *this;
    }

    Fraction& operator*=(const Fraction& rhs) {
        LL rn = rhs.n, rd = rhs.d;
        LL g1 = gcd(n, rd);
        n /= g1; rd /= g1;
        LL g2 = gcd(d, rn);
        d /= g2; rn /= g2;

        n *= rn;
        d *= rd;
        reduce();
        return *this;
    }

    Fraction& operator/=(const Fraction& rhs) {
        Fraction temp = Fraction(rhs.d, rhs.n);  // inverse
        return (*this) *=(temp);
    }

    static Fraction Zero() {
        return Fraction(0);
    }
};

bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.n == rhs.n && lhs.d == rhs.d;
}

bool operator!=(const Fraction& lhs, const Fraction& rhs) {
    return !(lhs == rhs.n);
}

Fraction operator+(Fraction lhs, const Fraction& rhs) {
    lhs += rhs;
    return lhs;
}

Fraction operator-(Fraction lhs, const Fraction& rhs) {
    lhs -= rhs;
    return lhs;
}

Fraction operator*(Fraction lhs, const Fraction& rhs) {
    lhs *= rhs;
    return lhs;
}

Fraction operator/(Fraction lhs, const Fraction& rhs) {
    lhs /= rhs;
    return lhs;
}

stringstream SS;

stringstream& eatline() {
    SS.clear();
    string line;
    getline(cin, line);
    SS.str(line);
    return SS;
}

typedef vector<Fraction> Vec;
typedef vector<Vec> Mat;

void dump(Mat& matrix) {
    for (Vec& vec : matrix) {
        for (Fraction& frac : vec) {
            cout << " " << frac.str();
        }
        cout << endl;
    }
}

void solve(Mat& matrix, int nu, int ne) {
    // Gaussian-Jordan
    int var = 0;
    int row = 0;
    while (row < ne && var < nu) {
        for (int tr=row;tr<ne;++tr) {
            if (matrix[tr][var] != Fraction::Zero()) {
                if (tr != row) {
                    swap(matrix[tr], matrix[row]);
                }
                break;
            }
        }
        Fraction coeff = matrix[row][var];
        if (coeff == Fraction::Zero()) {
            var++;
            continue;
        }
        for (int j=0;j<nu+1;++j) {
            matrix[row][j] /= coeff;
        }

        for (int i=0;i<ne;++i) {
            if (i == row) continue;
            Fraction mul = matrix[i][var];
            if (mul != Fraction::Zero()) {
                for (int j=0;j<nu+1;++j) {
                    matrix[i][j] -= (mul * matrix[row][j]);
                }
            }
        }
        row++;
        var++;
    }

    // count ranks
    int rank1 = 0, rank2 = 0;
    for (int i=0;i<ne;++i) {
        bool all_zero = true;
        for (int j=0;j<nu;++j) {
            if (matrix[i][j] != Fraction::Zero()) {
                all_zero = false;
                break;
            }
        }
        if (all_zero) {
            if (matrix[i][nu] != Fraction::Zero()) {
                rank2++;
            }
        } else {
            rank1++;
            rank2++;
        }
    }
    if (rank2 > rank1) {
        cout << "No Solution." << endl;
    } else if (rank1 < nu) {
        cout << "Infinitely many solutions containing " << nu-rank1 << " arbitrary constants." << endl;
    } else {
        // TODO: there could be some unexpected cases
        for (int i=0;i<nu;++i) {
            cout << "x[" << i+1 << "] = " << matrix[i][nu].str() << endl;
        }
    }
}

int main() {
    string line;
    int cases;
    int nu, ne;
    bool first = true;
    while (1) {
        eatline() >> cases;
        if (cases == 0) break;
        eatline() >> nu >> ne;
        Mat matrix(ne, Vec(nu+1, Fraction("0")));
        for (int i=0;i<ne;++i) {
            stringstream& ss = eatline();
            for (int j=0;j<nu+1;++j) {
                string expr;
                ss >> expr;
                matrix[i][j] = Fraction(expr);
            }
        }
        eatline();  // blank
        if (!first) cout << endl;
        cout << "Solution for Matrix System # " << cases << endl;
        solve(matrix, nu, ne);
        first = false;
    }
}
