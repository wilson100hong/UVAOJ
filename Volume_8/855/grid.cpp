#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int S, A, F;
        cin >> S >> A >> F;
        vector<int> streets;
        vector<int> aves;
        for (int i=0;i<F;++i) {
            int s, a;
            cin >> s >> a;
            streets.push_back(s);
            aves.push_back(a);
        }
        sort(streets.begin(), streets.end());
        sort(aves.begin(), aves.end());
        // find median

        int ms = streets[(streets.size()-1)/2];
        int ma = aves[(aves.size()-1)/2];
        cout << "(Street: " << ms << ", Avenue: " << ma << ")" << endl;

    }
}
