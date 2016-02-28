#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define eps (long double) (1e-3)
using namespace std;

long double A[210][210];
int n,m;

bool zero(long double u) {
	return (u < eps && u > -eps);
}

void solve() {
	int ans = 0;
	for (int u = 1; u <= min(n,m); u++) {		
		int x = 0; int y = 0;
		for (int i = u; i <= n; i++) {
			for (int j = u; j <= m; j++)
				if (!zero(A[i][j])) { x = i; y = j; break; }
			if (x) break;
		}
		if (!x) break;
		ans++;
		for (int i = 1; i <= m; i++) swap(A[u][i],A[x][i]);
		for (int i = 1; i <= n; i++) swap(A[i][u],A[i][y]);	   
		for (int i = u + 1; i <= n; i++) {
			long double k = A[i][u] / A[u][u];
			for (int j = 1; j <= m; j++) A[i][j] -= A[u][j] * k;
		}
		for (int i = u + 1; i <= m; i++) {
			long double k = A[u][i] / A[u][u];
			for (int j = 1; j <= n; j++) A[j][i] -= A[j][u] * k;
		}
	}
	printf("%d",ans);
}

int main() {
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			scanf("%Lf",&A[i][j]);
	solve();
	return 0;
}
