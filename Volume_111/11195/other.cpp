#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

char maps[16][16]; 

int dfs(int d, int n, int L, int M, int R)
{
	if (d >= n) {
		return 1;
	}
	int ans = 0;
	for (int i = 0; i < n; ++ i) {
		if (maps[d][i] != '*' && ((1<<i)&(L|M|R)) == 0) {
			ans += dfs(d+1, n, (L|(1<<i))<<1, M|(1<<i), (R|(1<<i))>>1);
		}
	}
	return ans;
}

int main()
{
	int n, cases = 1;
	while (~scanf("%d",&n) && n) {
		for (int i = 0; i < n; ++ i) {
			scanf("%s",maps[i]);
		}
		
		printf("Case %d: %d\n",cases ++, dfs(0, n, 0, 0, 0));
	}
	return 0;
}
