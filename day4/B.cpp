#include <cstdio>
#include <cstring>
#include <algorithm>
#define add(a,b) { a += b; }
using namespace std;

int ans;
int f[2][1 << 17];
int d[50][50],s[50][50];
int mark[50],co[50],n1,n2,n,m;
int wp[50];

//void add(int &a,int b) { a += b; return; }

void dfs(int c,int u) {
	co[u] = c;
	for (int i = 1; i <= n; i++) {
		if (!s[i][u] || co[i]) continue;
		dfs(3 - c,i);
	}
}

void dp(int st,int v,int k,int o) {
	add(f[o][st | wp[v]],f[o ^ 1][st]);
	if (k) add(f[o][st],f[o ^ 1][st]);
	return;
}

void solve(int st) {
	int b = 0;
	int sing = st;
	for (int i = 0; i < n2; i++)
		sing |= wp[i];
	if (sing != ((1 << (n1)) - 1)) return;
	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			if (d[i][j] && ((st >> i) & 1)) {
				b |= (1 << j);
			}
	for (int i = st; i < (1 << n1); i = (i + 1) | st)
		f[1][i] = 0;
	int o = 0; f[1][st] = 1;
	for (int i = 0; i < n2; i++) {
		for (int ts = st; ts < (1 << n1); ts = (ts + 1) | st)
			f[o][ts] = 0; 
		for (int ts = st; ts < (1 << n1); ts = (ts + 1) | st) {			
			add(f[o][ts | wp[i]],f[o ^ 1][ts]);
			if (((b >> i) & 1)) add(f[o][ts],f[o ^ 1][ts]);
			//dp(ts,i,((b >> i) & 1),o);
		}
		o ^= 1;
	}
	add(ans,f[o ^ 1][(1 << n1) - 1]);
}

int main() {
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= m; i++) {
		int a,b;
		scanf("%d %d",&a,&b);
		s[a][b] = s[b][a] = 1;
	}
	for (int i = 1; i <= n; i++) {
		if (co[i]) continue; 
		dfs(1,i);
	}
	
	int js = 0;
	for (int i = 1; i <= n; i++)
		if (co[i] == 1) js++;

	if (js > n - js) {
		for (int i = 1; i <= n; i++)
			co[i] = 3 - co[i];
	}
	
	for (int i = 1; i <= n; i++) {
		if (co[i] == 1) mark[i] = n1++;
		else mark[i] = n2++;
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (co[i] == 1 && co[j] == 2 && s[i][j])
				d[mark[i]][mark[j]] = s[i][j];
		}

	if (!n1) {
		printf("1\n"); return 0;
	}

	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n1; j++)
			wp[i] |= (d[j][i] << j);
	}
	
	for (int i = 0; i < (1 << n1); i++) solve(i);

	printf("%d",ans);
	return 0;
}
