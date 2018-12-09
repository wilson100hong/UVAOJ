#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int max(int a, int b) {
    return a > b ? a :b;
}

int main() {
    int n, d, r;
    while (cin >> n >> d >> r) {
        if (n==0 && d==0 && r==0) break;
        vector<int> morning;
        vector<int> evening;
        for (int i=0;i<n;++i) {
            int x;
            cin >> x;
            morning.push_back(x);
        }
        for (int i=0;i<n;++i) {
            int x;
            cin >> x;
            evening.push_back(x);
        }
        sort(morning.begin(), morning.end());
        sort(evening.begin(), evening.end());
        
        int total = 0;
        for (int i=0;i<n;++i) {
            int s = morning[i] + evening[n-i-1];
            total += max(0, s - d)* r;
        }
        cout << total << endl;

    }
}
