#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 410
#define INF (1 << 30)
using namespace std;

int w[maxn][maxn],f[maxn][maxn],px[maxn][maxn],py[maxn][maxn],co[maxn][maxn];
int ans,W,n,m;
bool flag;

bool dfs(int st) {
	for (int i = 1; i <= n; i++) f[i][0] = f[0][i] = INF;
	f[1][0] = 0; f[0][1] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			f[i][j] = INF;
			if (!((st >> co[i][j]) & 1)) continue;
			if (f[i][j] > f[i][j - 1] + w[i][j])
				f[i][j] = f[i][j - 1] + w[i][j], px[i][j] = i, py[i][j] = j - 1; 
			if (f[i][j] > f[i - 1][j] + w[i][j])
				f[i][j] = f[i - 1][j] + w[i][j], px[i][j] = i - 1, py[i][j] = j;
		}
	return (f[n][n] <= W);
}

void print(int x,int y) {	
	if (x != 1 || y != 1) 
		print(px[x][y],py[x][y]);
	printf("%d %d ",x,y);
}

int main() {
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	scanf("%d %d %d",&n,&m,&W);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d",&w[i][j]);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d",&co[i][j]), co[i][j]--;
	flag = false;
	for (ans = 0; ans <= m && !flag; ans++) {
		for (int st = 0; st < (1 << m); st++) {
			int js = 0;
			for (int i = 0; i < m; i++)
				js += ((st >> i) & 1);
			if (js != ans) continue;
			if (dfs(st)) {
				flag = true;
				break;
			}
		}
		if (flag) break;
	}
	if (flag) {
		printf("%d\n",ans);
		print(n,n);
	}
	else printf("-1");
	return 0;
}
