#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        if (n == 0) break;
        map<string, int> combs;
        int max = 0;
        for (int i=0;i<n;++i) {
            vector<int> courses;
            for (int j=0;j<5;++j) {
                int course;
                cin >> course;
                courses.push_back(course);
            }
            sort(courses.begin(), courses.end());
            string key;
            for (const int& course : courses) {
                key += to_string(course);
            }
            if (combs.count(key) == 0) {
                combs[key] = 0;
            }
            combs[key]++;
            if (combs[key] > max) {
                max = combs[key];
            }
        }
        
        int ans = 0;
        for (const auto& kv : combs) {
            if (kv.second == max) {
                ans += kv.second;
            }
        }
        cout << ans << endl;
    }
}
