#include <cstdio>
#include <cstring>
#include <algorithm>
#define midl ((L + R) >> 1)
#define midr (midl + 1)
#define INF (1 << 30)
#define maxn 2010000
using namespace std;

struct str { int v,nex,cap; } edge[maxn];
typedef int arr32[maxn];
arr32 fst,mark,markp,vis,d,que,lk,rk,ans,fa,du,A,B;
int n,m,e,top,root,seg_root,flow,s,t,cl;

void make_edge(int a,int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

void make_cap(int a,int b,int cap) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b; edge[e].cap = cap;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a; edge[e].cap = 0;
}

void dfs(int u,int pas,int f) {
	fa[u] = f; mark[u] = ++top;
	for (int i = fst[u]; i; i = edge[i].nex) {
		if (edge[i].v == pas) continue;
		dfs(edge[i].v,u,f);
	}
}

int build(int L,int R) {
	if (L == R) return L;
	int u = ++top;
	lk[u] = build(L,midl);
	rk[u] = build(midr,R);
	make_cap(u,lk[u],INF);
	make_cap(u,rk[u],INF);
	return u;
}

void build_edge(int u,int L,int R,int u_,int l,int r) {
	if (L == l && R == r) { make_cap(u_,u,INF); return; }
	if (r < midr) build_edge(lk[u],L,midl,u_,l,r);
	else if (l > midl) build_edge(rk[u],midr,R,u_,l,r);
	else {
		build_edge(lk[u],L,midl,u_,l,midl);
		build_edge(rk[u],midr,R,u_,midr,r);
	}
}

int ext(int u,int ma) {
	if (u == t || !ma) return ma;
	int f,flow = 0;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v;
		if (d[v] == d[u] + 1 && (f = ext(v,min(edge[i].cap,ma)))) {
			flow += f; ma -= f;
			edge[i].cap -= f; edge[i ^ 1].cap += f;
			if (!ma) return flow;
		}
	}
	d[u] = INF;
	return flow;
}

bool bfs() {
	int L = 0,R = 0;
	que[++R] = s; vis[s] = ++cl; d[s] = 0;
	while (L < R) {
		int u = que[++L];
		for (int i = fst[u]; i; i = edge[i].nex) {
			if (edge[i].cap && vis[edge[i].v] != cl) {
				vis[edge[i].v] = cl;
				d[edge[i].v] = d[u] + 1;
				que[++R] = edge[i].v;
			}
		}
	}
	return (vis[t] == cl);
}

void dinic() {
	while (bfs())
		flow += ext(s,INF);	
}

int backback(int u) {
	if (u >= markp[1]) return u;
	for (int i = fst[u]; i; i = edge[i].nex) {
		if (edge[i].cap) {
			edge[i].cap--;
			return backback(edge[i].v);
		}
	}
	return 0;
}

int main() {
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i < n; i++) {
		int a,b;
		scanf("%d %d",&a,&b);
		du[a]++; du[b]++;
		make_edge(a,b);
	}

	root = 0;
	for (int i = 1; i <= n; i++)
		if (du[i] > 2) root = i;
	if (!root) root = 1;
 	mark[root] = ++top;	

	for (int i = fst[root]; i; i = edge[i].nex) {
		dfs(edge[i].v,root,edge[i].v);
	}

	s = ++top; t = ++top;
	memset(fst,0,sizeof(fst)); e = 1; 
	seg_root = build(1,n);

	for (int i = 1; i <= n; i++) scanf("%d %d",&A[i],&B[i]);

	for (int i = 1; i <= n; i++) {
		markp[i] = ++top;
		make_cap(s,markp[i],1);
		if (B[i] == root) swap(A[i],B[i]);
		if (A[i] == root) {
			make_cap(markp[i],mark[root],INF);
			if (B[i] != root) build_edge(seg_root,1,n,markp[i],mark[fa[B[i]]],mark[B[i]]);
		} else {
			if (fa[A[i]] != fa[B[i]]) {
				make_cap(markp[i],mark[root],INF);
				build_edge(seg_root,1,n,markp[i],mark[fa[A[i]]],mark[A[i]]);
				build_edge(seg_root,1,n,markp[i],mark[fa[B[i]]],mark[B[i]]);
			} else {
				if (mark[A[i]] > mark[B[i]]) swap(A[i],B[i]);
				build_edge(seg_root,1,n,markp[i],mark[A[i]],mark[B[i]]);				
			}
		}
	}

	for (int i = 1; i <= n; i++)
		make_cap(mark[i],t,1);

	dinic();
	if (flow < n) { printf("No"); return 0; }			
	for (int i = 1; i <= n; i++) {
		int k = backback(mark[i]);
		ans[k] = i;
	}
	
	printf("Yes\n");
	for (int i = 1; i <= n; i++) printf("%d ",ans[markp[i]]);
	
	return 0;
}
