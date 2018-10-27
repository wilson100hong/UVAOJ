#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int M, int N) {
    if (M < N) swap(M, N);
    // M > N
    if (N == 1) return M;
    if (N == 2) {
        return (M/4)*4 + min(2, M%4)*2; 
    }

    return ((N+1)/2)*((M+1)/2) + (N/2)*(M/2);

}

int main() {
    int M, N;
    while (cin >> M >> N) {
        if (M==0 && N==0) break;
        int ans = solve(M, N);
        cout << ans << " knights may be placed on a " <<  M << " row " << N << " column board." << endl;
    }
}
