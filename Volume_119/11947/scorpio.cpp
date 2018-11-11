// NOTE: padding 0
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


int c2i(char c) {
    return c - '0';
}

string ZODS[]= {
    "capricorn",  // trick
    "aquarius", 
    "pisces",
    "aries",
    "taurus",
    "gemini",
    "cancer",
    "leo",
    "virgo",
    "libra",
    "scorpio",
    "sagittarius",
    "capricorn"
};
int ZOD_BEGINS[] = {
    0,
    21,  // Jan
    20,
    21,
    21,
    22,
    22,
    23,  // July
    22,
    24,
    24,
    23,
    23
};
string get_zodiac(int M, int D) {
    if (D >= ZOD_BEGINS[M]) return ZODS[M];
    return ZODS[M-1];
}

int MONTHS[] = {
    -1,
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31};

bool is_leap(int y) {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return y % 4 == 0;
}
int month_length(int Y, int M) {
    if (is_leap(Y) && M == 2) return 29;
    return MONTHS[M];
}

string padding(int n, int len) {
    string x = to_string(n);
    return string(len-x.size(), '0') + x;
}

void solve(const string& line) {
    int Y, M, D;
    M = c2i(line[0])*10 + c2i(line[1]);
    D = c2i(line[2])*10 + c2i(line[3]);
    Y = c2i(line[4])*1000 + c2i(line[5])*100 + c2i(line[6])*10 + c2i(line[7]);

    // advance 7*40 days
    int n = 40 * 7;
    while (month_length(Y, M) - D < n) {
        n -= (month_length(Y, M) - D + 1);
        D = 1;
        M++;
        if (M == 13) {
            Y++;
            M = 1;
        }
    }

    D += n;
    cout << padding(M, 2) << "/" << padding(D, 2) << "/" << padding(Y, 4) << " " << get_zodiac(M, D);
}

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int N;
    ss >> N;
    for (int i=1;i<=N;++i) {
        getline(cin, line);
        cout << i << " ";
        solve(line);
        cout << endl;
    }
}
