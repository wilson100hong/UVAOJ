#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool banana(const vector<int>& v) {
    return (v[0] + v[1] + v[2]) <= v[3];
}

int main() {
    int N, d;
    cin >> N;
    while (N--) {
        vector<int> v;
        for (int i=0;i<4;++i) {
            cin >> d;
            v.push_back(d);
        }

        sort(v.begin(), v.end());

        if (v[0] == v[1] && v[1] == v[2] && v[2] == v[3]) {
            cout << "square" << endl;
        } else if (v[0] == v[1] && v[2] == v[3]) {
            cout << "rectangle" << endl;
        } else if (banana(v)) {
            cout << "banana" << endl;
        } else {
            cout << "quadrangle" << endl;
        }
    }
}
