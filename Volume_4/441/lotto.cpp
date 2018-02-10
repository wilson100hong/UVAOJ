#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void dump(const vector<int>& ns) {
    for (int i=0;i<ns.size();++i) {
        if (i) cout << " ";
        cout << ns[i];
    }
    cout << endl;
}

void helper(const vector<int>& nums, int start, vector<int>& sofar) {
    if (sofar.size() == 6) dump(sofar);
    for (int i=start;i<nums.size();++i) {
        sofar.push_back(nums[i]);
        helper(nums, i+1, sofar);
        sofar.pop_back();
    }
}

void solve(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<int> sofar;
    helper(nums, 0, sofar);
}

int main() {
    int n;
    bool first = true;
    while (cin >> n) {
        if (!n) break;
        vector<int> nums;
        while (n--) {
            int x;
            cin >> x;
            nums.push_back(x);
        }

        if (!first) 
            cout << endl;
        else 
            first = false;
        solve(nums);

    }

}
