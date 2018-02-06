// 2018/2/6
//
// IDEA:
// 1. build SA and height
// 2. binary search on common substring length k
// 3. for each k, group height with barrier 'k', and see if there are any group has >=(n+2)/2 life froms
//
// TRAP:
// 1. when there is only one life form
//
//
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <unordered_set>
#include <set>
using namespace std;

pair<vector<int>, vector<int>> get_sa_height(const vector<int>& input) {
    vector<int> rank = input;
    int n = rank.size();
    vector<int> sa(n, -1);

    int radix = 256;
    vector<int> cnt(radix, 0);

    for (int c : rank) cnt[c]++;
    for (int i=1;i<radix;++i) cnt[i] += cnt[i-1];
    for (int i=n-1;i>=0;--i) sa[--cnt[rank[i]]] = i; 

    vector<int> sa2(n, 0);

    for (int p=1,k=1; p<n; k*=2, radix=p) {
        int s=0;
        for (int i=n-k;i<n;++i) sa2[s++] = i;
        for (int i=0;i<n;++i) {
            if (sa[i] >= k) sa2[s++] = sa[i]-k;
        }

        vector<int> rank2(n, 0);
        for (int i=0;i<n;++i) rank2[i] = rank[sa2[i]];

        cnt.assign(radix, 0);
        for (int i=0;i<n;++i) cnt[rank2[i]]++;
        for (int i=1;i<radix;++i) cnt[i] += cnt[i-1];
        for (int i=n-1;i>=0;--i) sa[--cnt[rank2[i]]] = sa2[i];

        rank2[sa[0]] = 0;
        p=1;
        for (int i=1;i<n;++i) {
            int ri = sa[i-1], rj = sa[i];
            rank2[sa[i]] = (rank[ri] == rank[rj] && rank[ri+k] == rank[rj+k]) ? p-1 : p++;
        }
        rank = rank2;
    }

    sa.erase(sa.begin());
    n = sa.size();
    for (int i=0;i<n;++i) rank[sa[i]] = i;

    vector<int> height(n, 0);
    int k = 0;
    for (int i=0;i<n;++i) {
        if (k>0) k--;
        if (rank[i] == 0) {
            height[0] = 0;
        } else {
            int j = sa[rank[i]-1];
            while (input[i+k] == input[j+k]) {
                k++;
            }
            height[rank[i]] = k;
        }
    }
    return make_pair(sa, height);
}

set<string> get_strings(const vector<string>& dnas,
        vector<int>& sa,
        vector<int>& height,
        int k) {
    int s=0, g=0, n=sa.size(), req = (dnas.size()+2)/2;
    set<string> ret;

    // 1. index to form_offset
    vector<pair<int, int>> form_offset(n, make_pair(0, 0));
    for (int i=0;i<dnas.size();++i) {
        for (int j=0;j<dnas[i].size();++j) {
            form_offset[s++] = make_pair(i, j);
        }
        if (i != dnas.size()-1) {
            form_offset[s++] = make_pair(-1, 0); // delimiter
        }
    }

    // 2. group height with barrier 'k'
    
    unordered_set<int> share;
    string prefix;
    bool added=false;

    s=0;
    while (s < n) {
        auto fo = form_offset[sa[s]];
        int h = height[s];
        s++;

        if (fo.first == -1) continue;  // delimiter
        
        if (h < k) {
            // potential prefix 
            prefix = dnas[fo.first].substr(fo.second, k);
            share.clear();
            added = false;  
        }
        share.insert(fo.first);
        if (!added && share.size() == req) {
            //cout << "form: " << fo.first << ", offset: " << fo.second << endl;
            ret.insert(prefix);
            added = true;
        }
    }
    return ret;
}

set<string> solve(const vector<string>& dnas) {
    // concatenate input by cantenating all dnas.
    // - deliminating by unshown letter
    // - ending with 0
    int sz = 0;
    for (const string& dna : dnas) sz += (dna.size() + 1);  // delimiter & ending '\0'
    vector<int> input(sz, 0);

    int i=0;
    int delimit = static_cast<int>('z') + 10;
    for (const string& dna : dnas) {
        for (char c : dna) {
            input[i++] = static_cast<int>(c);
        }
        input[i++] = delimit++;
    }
    if (i != sz) {
        cout << "ERROR!" << endl;
    }
    input[sz-1] = 0;

    vector<int> sa, height;
    tie(sa, height) = get_sa_height(input);

    // Binary search
    int n = dnas.size();
    int l = 1, r = input.size() / ((n+2)/2);  // (n+2)/2 is the minimum number of dnas to satisfy

    set<string> cand;
    while (l + 1 < r) {
        int m = (l+r)/2;  // m is the size we are looking for
        //if (feasible(dnas, sa, height, m)) {
            //l = m;
        //} else {
            //r = m - 1;
        //}
        cand = get_strings(dnas, sa, height, m); 
        if (!cand.empty()) {
            l = m;
            continue;
        } else {
            r = m - 1;
        }
    }


    cand = get_strings(dnas, sa, height, r);
    if (!cand.empty())  return cand;
        
    if (l != r) {
        cand = get_strings(dnas, sa, height, l);
        if (!cand.empty())  return cand;
    }

    return {"?"};
}

int main() {
    vector<int> sa, height;
    int n;
    bool first = true;
    while (cin >> n) {
        if (!n) break;
        vector<string> dnas;
        for (int i=0;i<n;++i) {
           string line;
           cin >> line;
           dnas.push_back(line);
        }
        if (!first) cout << endl;
        set<string> ans;
        if (dnas.size() == 1) {
            ans = {dnas[0]};
        } else {
            ans = solve(dnas);
        }
        // output
        for (const string& s : ans) cout << s << endl;

        first = false;
    }
}
