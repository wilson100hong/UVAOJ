#include <iostream>
#include <vector>

typedef unsigned long long ull;
using namespace std;

vector<ull> primes = {2};

void build_primes() {
    // build 3500
    ull n = 3;
    while (primes.size() < 3500) {
        bool is_prime = true;
        for (ull p : primes) {
            if (p*p > n) break;
            if (n % p == 0) {
                is_prime = false;
                break;
            }
        }

        if (is_prime) {
            primes.push_back(n);
        }
        n += 2;
    }

    /*
    for (ull p : primes) {
        cout << p << endl;
    }
    */
}

int joseph(int n) {
    int ans = 0;
    for (int i=2;i<=n;++i) {
        // https://blog.csdn.net/tingyun_say/article/details/52343897
        ans = (ans + primes[n-i]) % i;
    }
    return ans;
}

int main() {
    int n;
    build_primes();
    vector<int> ans = {0};  // n == 0
    for (int i=1;i<3502;++i) {
        //cout << "i: " << i << endl;
        ans.push_back(joseph(i));
    }
    while (cin >> n) {
        if (n == 0) break;
        cout << ans[n] + 1 << endl;
    }
}
