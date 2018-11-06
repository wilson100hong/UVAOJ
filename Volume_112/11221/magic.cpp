// NOTE: empty string returns 0.
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;

int square(int n) {
    // TODO
    int v = 1;
    while (v*v < n) {
        v++;
    }
    return v*v == n ? v : -1;
}
 
string reverse(const string& input) {
    string rev = input;
    int l=0, r=rev.size()-1;
    while (l < r) {
        swap(rev[l], rev[r]);
        l++; r--;
    }
    return rev;
}

bool diagonal(const string& s, int n) {
    // s.size() = n*n
    for (int i=0;i<n;++i) {
        for (int j=0;j<n;++j) {
            if (s[i*n+j] != s[j*n+i]) return false;
        }
    }
    return true;
}
string solve(const string& line) {
    string no_magic = "No magic :(";
    string s;
    s.reserve(line.size());
    for (char c : line) {
        if ('a' <= c && c <= 'z') {
            s.push_back(c);
        }
    }
    if (s.empty()) return to_string(0);

    int sq = square(s.size());
    if (sq < 0) return no_magic;
    string rs = reverse(s);
    if (rs != s) return no_magic;

    // Diagonal compare
    if (!diagonal(s, sq) || !diagonal(rs, sq)) return no_magic;
    return to_string(sq);
}


int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    int T;
    ss >> T;
    for (int t=1;t<=T;++t) {
        getline(cin, line);
        cout << "Case #" << t << ":" << endl;
        cout << solve(line) << endl;
    }
}
