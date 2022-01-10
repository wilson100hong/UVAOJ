#include <vector>
#include <iostream>
using namespace std;

vector<int> build_next(const string& p) {
    int n = p.size();
    vector<int> next(n, 0);
    next[0] = -1;
    int j = 0, k = -1;
    while (j < n - 1) {
        if (k == -1 || p[j] == p[k]) {
            ++j;
            ++k;
            // next[j] = k;
            /*optimization */
            if (p[j] != p[k]) {
                next[j] = k;
            } else {
                next[j] = next[k];
            }
        } else {
            k = next[k];
        }
    }
    return next;
}

int kmp(const string& s, const string& p) {
    vector<int> next = build(p);
    int m = s.size(), n = p.size();
    int i = 0, j = 0;
    while (i < m && j < n) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }    
    if (j == n) {
        return i - j;
    }
    return -1;
}

int main() {
    string s;
    cin >> s;
    string p;
    cin >> p;
    int find = kmp(s, p);
    cout << "find: " << find << endl;
}
