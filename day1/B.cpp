#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define maxn 2005
#define intl long long
#define lowbit(a) ((a) & (-(a)))
using namespace std;

int que[maxn];
char s[maxn][maxn];
int d[maxn][maxn / 31 + 10];
int dis[maxn][maxn];
int wp[(1 << 16) + 10];
int st[maxn / 31 + 10],ts[maxn / 31 + 10];
int n;

int main() {
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d",&n);
	for (int i = 0; i < n; i++) scanf("%s",s[i]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			if (s[i][j] == '1')
				d[i][j / 31] += 1 << (j % 31);
		}

	for (int i = 0; i <= 16; i++) wp[1 << i] = i;
	for (int t = 0; t < n; t++) {
		int L = 0, R = 0; 
		memset(st,0,sizeof(st));
		for (int i = 0; i < n; i++) st[i / 31] += (1 << (i % 31));
		st[t / 31] ^= (1 << (t % 31));
		que[++R] = t;
		while (L < R) {
			int u = que[++L];
			for (int i = 0; i <= (n - 1) / 31; i++) ts[i] = st[i] & d[u][i];
			for (int i = 0; i <= (n - 1) / 31; i++) {
				while (ts[i]) {
					int k = lowbit(ts[i]);
					if (k <= 1 << 16) k = wp[k];
					else k = 16 + wp[k >> 16];
					k += i * 31;
					dis[t][k] = dis[t][u] + 1;
					que[++R] = k;
					ts[i] -= lowbit(ts[i]);
					st[i] ^= 1 << (k % 31); 
				}
			}
		}
	}

	intl ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (dis[i][j] || i == j) ans += (intl) (dis[i][j] * dis[i][j]);
			else ans += (intl) (n * n);

	cout << ans << endl;
	return 0;
}
