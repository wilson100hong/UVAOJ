// Count inversion pairs:
// https://stackoverflow.com/questions/20990127/sorting-a-sequence-by-swapping-adjacent-elements-using-minimum-swaps/20990301#20990301
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

typedef unsigned long long ull;

vector<ull> merge_sort(const vector<ull>& list, ull* ans) {
    if (list.size() < 2) {
        return list;
    }

    int n = list.size();
    auto left = vector<ull>(list.begin(), list.begin() + n/2);
    auto right = vector<ull>(list.begin() + n/2, list.end());

    left = merge_sort(left, ans);
    right = merge_sort(right, ans);

    vector<ull> merged;
    merged.reserve(n);

    int i = 0, j = 0;
    while (i < left.size() || j < right.size()) {
        if (i == left.size() || (j < right.size() && left[i] > right[j])) {
            // pick right
            *ans = (*ans + left.size() - i);
            merged.push_back(right[j]);
            j++;
        } else if (j == right.size() || (i < left.size() && left[i] < right[j])) {
           // pick left 
           merged.push_back(left[i]);
           i++;
        }
    }
    return merged;
}

int main() {
    ull n;
    while (cin >> n) {
        vector<ull> list;
        list.reserve(n);
        for (int i=0;i<n;++i) {
            ull s;
            cin >> s;
            list.push_back(s);
        }
        ull ans = 0;
        vector<ull> sorted = merge_sort(list, &ans);
        cout << ans << endl;
    }
}
