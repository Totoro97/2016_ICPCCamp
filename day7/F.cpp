#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 201000
using namespace std;

void dfs(int u) {
	dep[u] = dep[fa[u]] + 1;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v = edge[i].v; if (fa[u] == v) continue;
		fa[v] = u; 
		st[v][0] = u; co[v] = edge[i].c;
		dfs(v);
	}
	return;
}

bool cmp(int a,int b) {
	return dep[a] > dep[b];
}

int main() {
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i < n; i++) {
		int a,b;
		scanf("%d %d %d",&a,&b,&c);
		st[c] = 1;
		make_edge(a,b,c);
	}
	for (poi i = st.begin(); i != st.end(); i++) {
		i -> second = top++;
		val[top - 1] = i -> first;
	}
	for (int i = 1; i <= e; i++) edge[i].c = st[edge[i].c];
	dfs(1);
	for (int i = 1; i <= n; i++) p[i] = i;
	sort(p + 1,p + n + 1,cmp); mark[1] = ++tp;
	sou[1] = 1;
	for (int i = 1; i <= n; i++) {
		int u = p[i];
		if (mark[u]) continue;
		bool flag = false; int v = u;
		for (int k = base; k; k--) {
			v = fa[v];
			if (mark[v]) {
				flag = true;
				break;
			}
		}
		if (flag) continue;
		mark[v] = ++tp;
		sou[tp] = v;
	}

	for (int i = 1; i <= tp; i++) {
		for (int u = sou[i]; u != 1; u = fa[u])
			bi[i][co[u] / 63] |= 1LL << (co[u] % 63);
	}

	prepare();
	for (; m; m--) {		
		for (int i = 0; i <= n / 63; i++) A[i] = B[i] = 0;
		
	}
	return 0;
}
