#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <tuple>

using namespace std;
 
class SuffixArrayBuilder {
public:

    int RankComp(const vector<int>& rank, int i, int j, int k) {
        return rank[i] == rank[j] && rank[i+k] == rank[j+k];
    }

    // Build suffix array and height using doubling algorithm: O(nlogn)
    pair<vector<int>, vector<int>> Build(const string& input, int radix=256) {
        // rank default to the character itself
        vector<int> rank(input.size()+1, 0);
        for (int i=0;i<input.size();i++) {
            rank[i] = static_cast<int>(input[i]);
        }
        int n = rank.size();
        vector<int> sa(n, -1);
        vector<int> cnt(radix, 0);

        // radix sort on single character
        for (int c : rank) cnt[c]++;
        for (int i=1;i<radix;++i) cnt[i] += cnt[i-1];
        for (int i=n-1;i>=0;--i) sa[--cnt[rank[i]]] = i;

        vector<int> sa2(n, 0);  // temp

        // p is the number of unique ranks. 
        for (int p=1,k=1; p<n; k*=2, radix=p) {
            // k is the length of substring for radix sort this round. k doubles up in each round.
            // radix sort ends when all suffix has unique rank (p >= n).

            // let s(a,b) denotes str.substr(a, b): start on index a with length b
            // since s(i,2k) = s(i,k) + s(i+k,k)
            // then sorting on substrings length 2*k can be viewed as radix sort on two digits:
            //   1) lower digit: s(i+k,k)  
            //   2) higher digit: s(i,k)
            // where is deduced from previous round (k)

            // also note that there will be substrings does not have lower digit (length <= k), so we separate infix to two parts:
            //   1) substring length > k: s(0,2k), s(1,2k)...s(n-2k,2k), s(n-2k+1,2k-1)...s(n-k+1, k+1)
            //   2) substring length <= k: s(n-k,k), s(n-k+1,k-1)...s(n-1,1)
            // part 2 dose not have lower digit, means it has smallest lower digit ('\0....'). So we can just put part2 priort than part1 in lower part

            // 1. radix sort on lower digit
            int s=0;
            for (int i=n-k;i<n;++i)  sa2[s++] = i;   // just copy part 2 
            for (int i=0;i<n;++i) {
                // shift left by k, since suffix(sa[i]) is the lower part of suffix(sa[i]-k)
                if (sa[i] >= k) sa2[s++] = sa[i]-k;
            }

            // 2. radix sort on higher digit
            vector<int> rank2(n, 0);
            for (int i=0;i<n;++i) rank2[i] = rank[sa2[i]];  // the index of rank2 does not matter here, we just want to collect all ranks

            cnt.assign(radix, 0);
            for (int i=0;i<n;++i) cnt[rank2[i]]++;
            for (int i=1;i<radix;++i) cnt[i] += cnt[i-1];
            for (int i=n-1;i>=0;--i) sa[--cnt[rank2[i]]] = sa2[i];

            // compute new ranks
            rank2[sa[0]] = 0;
            p = 1;  // at least one rank
            for (int i=1;i<n;++i) rank2[sa[i]] = RankComp(rank, sa[i-1], sa[i], k) ? p-1 : p++;

            rank = rank2;  // TODO: this can be optimized by swap pointers
        }


        // remove the '\0'
        sa.erase(sa.begin());

        // build height
        n = sa.size(); // reset n size
        for (int i=0;i<n;++i) rank[sa[i]] = i;

        vector<int> height(n, 0);
        // height[rank[i]] >= height[rank[i]-1]-1
        // https://icymind.com/calculate-height-array/
        int k = 0;  // k is the previous height value
        for(int i=0;i<n;++i) {
            if (k > 0) k--;  
            if (rank[i] == 0) {
                height[0] = 0;
            } else {
                int j = sa[rank[i]-1];  // suffix(j) is the closest prior suffix before suffix(i) in SA
                while (input[i+k] == input[j+k]) {
                    k++;
                }
                height[rank[i]] = k;
            }
        }

        return make_pair(sa, height);
    }
};


int main() {
    //string input = "abracadabra0AbRa4Cad14abra";
    string input = "abcdefg$bcdefgh%cdefghi";
    //string input = "aabaaaab";
    vector<int> sa, height;
    SuffixArrayBuilder builder;
    tie(sa, height) = builder.Build(input);
    for (int i : sa)
        cout << i << " ";
    cout << endl;

    for (int h : height)
        cout << h << " ";
    cout << endl;
}
