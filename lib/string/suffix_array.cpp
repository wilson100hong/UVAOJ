#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
 

int RankComp(const vector<int>& rank, int i, int j, int k) {
    return rank[i] == rank[j] && rank[i+k] == rank[j+k];
}

// Get suffix array usig doubling algorithm, O(nlogn)
//   str: input string
//   radix: characters count
vector<int> GetSA(const string& input, int radix=256) {
    // We append null character at the end of the string to simplify the comparision
    vector<int> rank(input.size()+1, 0);
    for (int i=0;i<input.size();++i) 
        rank[i] = static_cast<int>(input[i]);

    int n = rank.size();

    // suffix array to return
    vector<int> sa(n, -1);

    // Define k-infix: infix with length k
    // sort 1-infix using radix sort
    vector<int> sum(radix, 0);
    for (int c : rank)
        sum[c]++;
    for (int j=1;j<radix;++j) 
        sum[j] += sum[j-1];
    for (int i=n-1;i>=0;--i)
        sa[--sum[rank[i]]] = i;

    vector<int> sa2(n, 0);  // temporary

    int p = 1;  // p is the number of unique ranks, this will be the new radix 
    for (int k=1; p<n; k*=2,radix=p) {
        // In each round, we sort 2k-infix (infix with length 2*k). Remember that as k grows, eventually all 2k-infix becomes suffix.
        // 
        // To save some typing, lets denote I(a,b) as the infix  {str[a], str[a+1], ... str[a+b-1]}, In c++, it is str.substr(a, b)
        // 
        // Here is the key part: an infix can be presented by the concantenation of two infix:
        // I(i,2k) = I(i,k)I(i+k,k)
        // The implies the sorting of I(i,2k) can be done by radix sort with 2 digits:
        // In round 1, sort on 2nd digit I(i+k,K)
        // In round 2, sort on on 1st digit I(i,k)
        // `
        // However, there are some infix does not have 2nd digit (length <= k) We split infix into two groups:
        //   group 1 (G1): I(0,2k), I(1,2k), ... I(n-2k,2k), I(n-2k+1,2k-1)...I(n-k+1,k+1)
        //   group 2 (G2): I(n-k,k), I(n-k+1,k-1),... I(n-1, 1)
        // 
        // Be careful that G2 has no 2nd digit. This means G2 has smallest 2nd digit, so in round 1 we can just put all G2 prior than G1.
        
        // Round 1
        // Elements in G2
        int s = 0;
        for (int i=n-k;i<n;++i)
            sa2[s++] = i;
        // Elements in G1
        for (int i=0; i<n; ++i) {
            if (sa[i] >= k) {
                sa2[s++] = sa[i]-k;
            }
        }

        // Round 2
        vector<int> rank2(n, 0);
        for (int i=0;i<n;++i)
            rank2[i] = rank[sa2[i]];

        sum.assign(radix, 0);
        for (int i=0;i<n;++i)
            sum[rank2[i]]++;
        for (int i=1;i<radix;++i)
            sum[i] += sum[i-1];
       
        for (int i=n-1;i>=0;--i)
            sa[--sum[rank2[i]]] = sa2[i];

        // Compute new rank
        rank2[sa[0]] = 0;
        p = 1;
        for(int i=1; i < n; i++)
            rank2[sa[i]] = RankComp(rank, sa[i-1], sa[i], k) ? p-1 : p++;
        
        rank = rank2;  // TODO: this can be optimize by swap pointers
    }
        
    auto it = find(sa.begin(), sa.end(), n-1);
    sa.erase(it);
    return sa;
}

// height[i] is the Longest Common Prefix (LCP) between suffix[sa[i]] and suffix[sa[i-1]]
vector<int> GetHeightFromSA(const string& input, const vector<int>& sa) {
    int n = sa.size();
    vector<int> rank(n, 0);
    for (int i=0;i<n;++i)
        rank[sa[i]] = i;

    
    // height[rank[i]] >= height[rank[i]-1]-1
    // https://icymind.com/calculate-height-array/
    vector<int> height(n, 0);
    int k = 0;
    for(int i=0;i<n;++i) {
        if (k > 0)
            k--;
        if (rank[i] == 0) {
            height[0] = 0;
        } else {
            int j = sa[rank[i]-1];  // suffix(j) is the suffix before suffix(i) in SA
            while (input[i+k] == input[j+k]) {
                k++;
            }
            height[rank[i]] = k;
        }
    }
    return height;
}


int main() {
    //string input = "abracadabra0AbRa4Cad14abra";
    string input = "aabaaaab";
    vector<int> sa = GetSA(input);
    for (int i : sa)
        cout << i << " ";
    cout << endl;

    vector<int> height = GetHeightFromSA(input, sa);
    for (int h : height)
        cout << h << " ";
    cout << endl;
}
