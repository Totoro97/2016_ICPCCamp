#include <cstdio>
#include <cstring>
#include <algorithm>
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define maxn 210000
using namespace std;

struct str { int v,nex; } edge[maxn];

int que[maxn];
int lk[maxn * 20],rk[maxn * 20], val[maxn * 20];
int root[maxn],fst[maxn],fail[maxn];
int top,e,c[maxn],fa[maxn],n;

void make_edge(int a,int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
}

int add(int u,int L,int R,int c,int v) {
	if (L == R) {
		val[++top] = v;
		return top;
	}
	int now = ++top;
	if (c < midr) {
		rk[now] = rk[u];
		lk[now] = add(lk[u],L,midl,c,v);	   
	} else {
		lk[now] = lk[u];
		rk[now] = add(rk[u],midr,R,c,v);
	}
	return now;
}

int find(int u,int L,int R,int c) {
	if (L == R) return val[u];
	if (c < midr) return find(lk[u],L,midl,c);
	else return find(rk[u],midr,R,c);
}

void bfs() {
	int L = 0, R = 0;
	que[++R] = 0;
	while (L < R) {
		int u = que[++L];
		root[u] = root[fail[u]];
		for (int i = fst[u]; i; i = edge[i].nex) root[u] = add(root[u],0,n,c[edge[i].v],edge[i].v);
		for (int i = fst[u]; i; i = edge[i].nex) {
			int v = edge[i].v;
			fail[v] = find(root[fail[u]],0,n,c[v]);
			if (fail[v] == v) fail[v] = 0;
			que[++R] = v;
		}
	}
}

int main() {
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d",&fa[i]);
	for (int i = 1; i <= n; i++) scanf("%d",&c[i]);
	for (int i = 1; i <= n; i++) make_edge(fa[i],i);
	bfs();
	for (int i = 1; i <= n; i++) printf("%d ",fail[i]);
	return 0;
}
