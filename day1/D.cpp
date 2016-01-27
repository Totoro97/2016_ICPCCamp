#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF (1 << 25)
using namespace std;

int ans[510],p[510];
char f[510][510];
int d[510][510];
int n,m,top,vis[510];

bool dfs(int u) {
	ans[++top] = u; vis[u] = 1;
	if (top == n) {
		if (d[u][ans[1]] <= m) return true;
		top--; vis[u] = 0;
		return false;
	}
	for (int v = 1; v <= n; v++) {
		if (d[u][p[v]] <= m && !vis[p[v]]) {
			if (dfs(p[v])) return true;			
		}
	}
	vis[u] = 0; top--;
	return false;
}

int main() {
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++)
		scanf("%s",f[i] + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			d[i][j] = f[i][j] == '1' ? 1 : INF;
		}
	for (int i = 1; i <= n; i++) p[i] = i;
	srand(173);
	random_shuffle(p + 1,p + n + 1);
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
	dfs(p[1]);
	for (int i = 1; i <= n; i++) printf("%d ",ans[i]);
	return 0;
}
