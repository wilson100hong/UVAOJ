#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <map>
#include <set>

using namespace std;

int abs(int a) {
    return a > 0 ? a : -a;
}
int ParseFixedInt(const string& str) {
    int res = 0;
    bool neg = false;
    int i=0;
    while (i < str.size()) {
        char c = str[i++];
        if (c == '-') {
            neg = true;
        } else if (c >= '0' && c <= '9') {
            res = res*10 + (c-'0');
        }  // ignore '.'
    }

    return res * (neg? -1 : 1);
}

pair<int, int> ParsePoint(const string& line) {
    stringstream ss(line);
    string xstr, ystr;
    ss >> xstr; ss>> ystr;
    return make_pair(ParseFixedInt(xstr), ParseFixedInt(ystr));
}

int gcd(int a, int b) {
    if (b > a) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a%b);
}

int main() {
    int T;
    string line;
    cin >> T;  getline(cin, line);
    for (int t=1;t<=T;++t) {
        set<pair<int, int>> ps;
        cout << "Data set #" << t << " contains ";
        int N;
        cin >> N; getline(cin, line);
        int max_aligned = 0;
        for (int i=0;i<N;++i) {
            getline(cin, line);
            pair<int, int> point = ParsePoint(line);
            ps.insert(point);
        }
        if (ps.size()  == 1) {
            cout << "a single gnu." << endl;
            continue;
        }

        vector<pair<int, int>> points;
        for (auto p : ps) points.push_back(p);

        for (int i=0;i<points.size();++i) {
            map<pair<int, int>, int> slope;
            auto p1= points[i];
            for (int j=i+1;j<points.size();++j) {
                auto p2 = points[j];
                int dx = p2.first - p1.first, dy = p2.second - p1.second;
                int g = gcd(abs(dx), abs(dy));
                if (g> 0) {
                    dx /= g;
                    dy /= g;
                }
                slope[make_pair(dx, dy)]++;
            }

            for (auto& kv : slope) {
                if (kv.second+1 > max_aligned) max_aligned = kv.second+1;
            }
        }

        cout << points.size() << " gnus, out of which a maximum of " << max_aligned << " are aligned." << endl;
    }
}
