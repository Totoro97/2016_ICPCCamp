#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 510
#define INF (1 << 20)
using namespace std;

int n,m,A[maxn],B[maxn];
int f[maxn][maxn],g[maxn][maxn];
int shang[maxn];
bool flag = false;

int main() {
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]);
	for (int i = 1; i <= m; i++) scanf("%d",&B[i]);	
	if (n == 1) { printf("Yes"); return 0; }
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
			f[j][i] = -INF;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++)
			g[j][i] = INF;
	f[1][0] = m;
	g[m][0] = 1;
	int L = 1, R = n;
	
	for (int i = 1; i <= n; i++) {
		if (A[i] == L) shang[i] = 0, L++;
		else shang[i] = 1, R--;
	}
	
	for (int i = 1; i <= m; i++) {
		for (int k = n - 1; k >= 0; k--) {
			for (int L = 1; L <= m; L++) {
				if (L > B[i]) break;
				if (f[L][k] < B[i]) continue;
				int R = f[L][k];
				if (L <= B[i] && R >= B[i] && k == n - 1) flag = true;
				if (shang[k + 1]) {
					f[L][k + 1] = max(f[L][k + 1],B[i] - 1);
					g[B[i] - 1][k + 1] = min(g[B[i] - 1][k + 1],L);
				} else {
					f[B[i] + 1][k + 1] = max(f[B[i] + 1][k + 1],R);
					g[R][k + 1] = min(g[R][k + 1],B[i] + 1);
				}
			}
			for (int R = m; R >= 1; R--) {
				if (R < B[i]) break;
				if (g[R][k] > B[i]) continue;
				int L = g[R][k];
				if (L <= B[i] && R >= B[i] && k == n - 1) flag = true;
				if (shang[k + 1]) {
					f[L][k + 1] = max(f[L][k + 1],B[i] - 1);
					g[B[i] - 1][k + 1] = min(g[B[i] - 1][k + 1],L);
				} else {
					f[B[i] + 1][k + 1] = max(f[B[i] + 1][k + 1],R);
					g[R][k + 1] = min(g[R][k + 1],B[i] + 1);
				}
			}
		}
	}
	if (flag) printf("Yes");
	else printf("No");
	return 0;
}
