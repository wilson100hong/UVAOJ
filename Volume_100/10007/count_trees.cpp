#include <iostream>
#include <string>
using namespace std;

// 2016/11/22
// STAR: 
// SKILL: catalan number, big number 
// TRAP:

string rstrip_zero(const string& s) {
    int cur = 0;
    while (s[cur] == '0' && cur < s.size()) {
        cur++;
    }
    return cur >= s.size() ? "0" : s.substr(cur);
}

string bigmul(const string& s1, const string& s2) {
    int n1 = s1.size(), n2 = s2.size();
    int n = n1+n2;
    string res(n, '0');
    int carry = 0;
    for (int i=n1-1;i>=0;--i) {
        int d1 = s1[i]-'0';
        for (int j=n2-1;j>=0;--j) {
            int d2 = s2[j]-'0';
            int sum = d1*d2 + carry + (res[i+j+1]-'0');
            res[i+j+1] = (sum % 10) + '0';
            carry = sum / 10;
        }
        // cursor start at i (i+j+1-1 where j = 0) 
        int cur = i;
        while (carry > 0 && cur >=0) {
            int sum = (res[cur]-'0') + carry;
            res[cur] = (sum % 10) + '0';
            carry = sum/10;
            cur--;
        }
    }
    return rstrip_zero(res);
}

// return C(n)*n! where C() is catalan number
// reduce to (n+2)*(n+3)*...*(2n)
string solve(int n) {
    string res = "1";
    for (int i=n+2;i<=2*n;++i) {
        res = bigmul(res, to_string(i));
    }
    return res;
}

int main() {
    int n;
    while (cin >> n) {
        if (n==0) break;
        cout << solve(n) << endl;
    }
}
