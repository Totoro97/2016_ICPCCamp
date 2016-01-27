#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 201000
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define lk (u << 1)
#define rk ((u << 1) + 1)
#define uint unsigned long long
#define intl long long
using namespace std;

const uint p = (uint) 229591;

int n,m;
int fa[maxn],nex[maxn],fst[maxn],num[maxn];
uint val[maxn << 2],fac[maxn];

uint find(int u,int L,int R,int l,int r) {
	if (L == l && R == r) return val[u];
	if (r < midr) return find(lk,L,midl,l,r);
	else if (l > midl) return find(rk,midr,R,l,r);
	else {
		uint A = find(lk,L,midl,l,midl);
		uint B = find(rk,midr,R,midr,r);
		return (A + B * fac[midr - l]);
	}
}

void change(int u,int L,int R,int k,int v) {
	if (L == R) { val[u] = v; return; }
	if (k < midr) change(lk,L,midl,k,v);
	else change(rk,midr,R,k,v);
	val[u] = val[lk] + val[rk] * fac[midr - L];
	return;
}

void merge(int a,int b) {
	a = fa[a]; b = fa[b];
	if (num[a] < num[b]) swap(a,b);
	int k;
	for (int i = fst[b]; i; i = k) {
		k = nex[i];
		nex[i] = fst[a]; fst[a] = i;
		fa[i] = a;
		change(1,1,n,i,a);
	}
	num[a] += num[b];
}

void solve(int a,int b,int c) {
	while (true) {
		if (!c) return;
		if (find(1,1,n,a,a + c - 1) == find(1,1,n,b,b + c - 1)) return;
		int L = 1, R = c;
		while (L < R) {
			int mid = (L + R) >> 1;
			if (find(1,1,n,a,a + mid - 1) == find(1,1,n,b,b + mid - 1)) L = mid + 1;
			else R = mid;
		}
		merge(a + L - 1,b + L - 1);
		a += L; b += L; c -= L;
	}
}

void build(int u,int L,int R) {
	if (L == R) { val[u] = (uint) L; return; }
	build(lk,L,midl);
	build(rk,midr,R);
	val[u] = val[lk] + val[rk] * fac[midr - L];
}

void init() {
	for (int i = 1; i <= n; i++) fa[i] = fst[i] = i;
	for (int i = 1; i <= n; i++) num[i] = 1;
	for (int i = 1; i <= n; i++) nex[i] = 0;
	build(1,1,n);
}

int main() {
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
	fac[0] = 1;
	for (int i = 1; i <= 200001; i++) fac[i] = fac[i - 1] * p;	
	while (scanf("%d %d",&n,&m) != EOF) {
		init();
		for (; m; m--) {
			int a,b,c;
			scanf("%d %d %d",&a,&b,&c);
			solve(a,b,c);
		}
		intl ans = 1LL;
		for (int i = 1; i <= n; i++) if (fa[i] == i) ans = ans * 26LL % 1000000007LL;
		printf("%d\n",(int) ans);
	}
	return 0;
}
