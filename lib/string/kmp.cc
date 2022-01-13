#include <vector>
#include <iostream>
using namespace std;

vector<int> build_lps(const string& p) {
    int n = p.size();
    vector<int> lps(n, 0);
    lps[0] = -1;
    int j = 0, k = -1;
    while (j < n - 1) {
        if (k == -1 || p[j] == p[k]) {
            ++j;
            ++k;
            // lps[j] = k;
            /*optimization */
            if (p[j] != p[k]) {
                lps[j] = k;
            } else {
                lps[j] = lps[k];
            }
        } else {
            k = lps[k];
        }
    }
    return lps;
}

// TODO: extend to return multiple occurence
int kmp(const string& s, const string& p) {
    vector<int> lps = build_lps(p);
    int m = s.size(), n = p.size();
    int i = 0, j = 0;
    while (i < m && j < n) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        } else {
            j = lps[j];
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
