#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF (1 << 30)
using namespace std;
int ans,n,m,o;
int f[2][510][510];
int A[510],B[510];
				 
int main() {
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]);
	for (int i = 1; i <= m; i++) scanf("%d",&B[i]);
	sort(A + 1,A + n + 1);
	o = 1;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			f[0][i][j] = INF;
	f[0][1][n] = 0;	
	for (int t = 1; t <= m; t++) {
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				f[o][i][j] = INF;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				f[o][min(i * B[t],n)][j] = min(f[o][min(i * B[t],n)][j],f[o ^ 1][i][j]);
		for (int i = n; i >= 1; i--)
			for (int j = n; j >= 1; j--)
				f[o][i - 1][j - 1] = min(f[o][i - 1][j - 1],f[o][i][j] + A[j] * t);
		o ^= 1;
	}
	ans = INF;
	for (int i = 0; i <= n; i++) ans = min(ans,f[o ^ 1][i][0]);
	printf("%d",ans);
	return 0;
}
