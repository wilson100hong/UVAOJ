#include <iostream>
using namespace std;

typedef unsigned long long ULL;
int main() {
    ULL N;
    while (cin >> N) {
        cout << ((N+1)/2)*(N+1)*3 - 9 << endl;
    }

}
