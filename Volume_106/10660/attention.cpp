#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <tuple>
using namespace std;

int abs(int x) {
    return x > 0 ? x : -x;
}
int min(int a, int b) {
    return a < b ? a : b;
}
int cost(int i, int j) {
    int ri = i/5;
    int ci = i%5;
    int rj = j/5;
    int cj = j%5;
    return abs(ri-rj) + abs(ci-cj);
}

int cost(const vector<int>& city, const vector<int> areas) {
    int total = 0;
    for (int i=0;i<25;++i) {
        int min_cost = numeric_limits<int>::max();
        for (int j: areas) {
            min_cost = min(min_cost, cost(i, j) * city[i]);
        }
        total += min_cost;
    }
    return total;
}

// cost, areas
pair<int, vector<int>> dfs(const vector<int>& city, vector<int>& areas) {
    if (areas.size() == 5) {
        return {cost(city, areas), areas};
    }
    int min_cost = numeric_limits<int>::max();
    vector<int> min_areas;

    int start = (areas.empty() ? 0 : areas.back() + 1);
    for (int i=start;i<25;++i) {
        areas.push_back(i);
        int c; 
        vector<int> a;
        tie(c, a) = dfs(city, areas);
        if (c < min_cost) {
            min_cost = c;
            min_areas = a;
        }
        areas.pop_back();
    }
    return {min_cost, min_areas};
}

vector<int> solve(const vector<int>& city) {
    vector<int> areas;
    int c;
    vector<int> ans;
    tie(c, ans) = dfs(city, areas);
    return ans;
}


int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> city(25, 0);
        while (n--) {
            int row, col, pop;
            cin >> row >> col >> pop;
            city[row*5+col] = pop;
        }
        vector<int> areas = solve(city);
        for (int i=0;i<5;++i) {
            if (i>0) cout << " ";
            cout << areas[i];
        }
        cout << endl;
    }
}
