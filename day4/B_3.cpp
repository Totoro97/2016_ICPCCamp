#include <cstdio>
#include <cstring>
#include <algorithm>
#define add(a,b) { a += b; }
#define intl long long
using namespace std;

int ans;
int d[50][50],s[50][50];
int mark[50],co[50],n1,n2,n,m;
int wp[50],pw[50];
intl f[1 << 17];
//void add(int &a,int b) { a += b; return; }

void dfs(int c,int u) {
	co[u] = c;
	for (int i = 1; i <= n; i++) {
		if (!s[i][u] || co[i]) continue;
		dfs(3 - c,i);
	}
}

void solve(int st) {
	int b = 0;
	for (int i = 0; i < n1; i++)
		if ((st >> i) & 1) b |= pw[i];
	int st_ = st, k = 0;	
	for (int i = 0; i < n2; i++) {
		if (!((b >> i) & 1)) st_ |= wp[i], k++;
	}
	st_ ^= ((1 << n1) - 1);
	ans += (int) (f[st_] >> k);
}

int main() {
	freopen("B.in","r",stdin);
	freopen("B_3.out","w",stdout);
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

	for (int i = 0; i < n1; i++)
		for (int j = 0; j < n2; j++)
			if (d[i][j]) wp[j] |= (1 << i), pw[i] |= (1 << j);

	f[0] = 1;

	for (int i = 0; i < n2; i++)
		for (int j = ((1 << n1) - 1); j >= 0; j--)
			f[j | wp[i]] += f[j];

	for (int k = 0; k < n1; k++)
		for (int st = (1 << n1) - 1; st >= 0; st--)
			if (!((st >> k) & 1)) f[st] += f[st ^ (1 << k)];

	for (int st = 0; st < (1 << n1); st++)
		solve(st);

	printf("%d",ans);
	return 0;
}
