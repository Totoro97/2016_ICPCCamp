#include <cstdio>
#include <cstring>
#include <algorithm>
#define Rand(a) (abs(rand() * rand() + rand()) % (a) + 1)
#define maxn 2001000
#define intl long long
#define INF (1 << 30)
using namespace std;

struct str { int v,nex; } edge[maxn];

typedef int arr32[maxn];
arr32 fst,tree,pos,end_pos,sou,js,A,B,ans;
typedef intl arr64[maxn];
arr64 sum,w;
int st[maxn][20],e,n,m,q,top,tp,wp,t;
int now[20],cuts[20];
pair<int,int> inter[20];

void make_edge(int a,int b) {
	edge[++e].nex = fst[a]; fst[a] = e; edge[e].v = b;
	edge[++e].nex = fst[b]; fst[b] = e; edge[e].v = a;
}

int dfs(int u) {
	pos[u] = end_pos[u] = ++top; sou[top] = u;
	for (int i = fst[u]; i; i = edge[i].nex) {
		int v;
		if ((v = edge[i].v) == st[u][0]) continue;
		st[v][0] = u;
		end_pos[u] = dfs(v);		
	}
	return end_pos[u];
}

intl size(int u) { return (sum[end_pos[u]] - sum[pos[u] - 1]); }

intl get_size(int u) {
	intl ans = size(u);
	for (int i = 1; i <= tp; i++)
		if (pos[now[i]] >= pos[u] && pos[now[i]] <= end_pos[u]) {
			ans -= size(now[i]);
		}
	return ans;
}

bool pmc(int a,int b)  { return size(a) < size(b); }

void prepare() {
	for (int j = 1; j <= 17; j++)
		for (int i = 1; i <= n; i++)
			st[i][j] = st[st[i][j - 1]][j - 1];
	for (int u = 1; u <= n; u++) {
		wp = 0;
		for (int i = fst[u]; i; i = edge[i].nex) {
			if (st[u][0] == edge[i].v) continue;
			js[++wp] = edge[i].v;
		}
		sort(js + 1,js + wp + 1,pmc);
		for (int i = 1; i <= wp; i++) {
			edge[++e].nex = tree[u]; tree[u] = e; edge[e].v = js[i];
		}
	}
}

bool cmp(int a,int b) { return pos[a] < pos[b]; }

int Random() {
	int N = 0;
	for (int i = 1; i <= t; i++) N += inter[i].second - inter[i].first + 1;
	N = Rand(N);
	for (int i = 1; i <= t; i++) {
		if (N <= inter[i].second - inter[i].first + 1)
			return sou[inter[i].first + N - 1];
		else N -= (inter[i].second - inter[i].first + 1);
	}
	return 0;
}

bool check(int u,intl N) {
	for (int i = tree[u]; i; i = edge[i].nex) {
		if (size(edge[i].v) <= N >> 1) return true;
		else if (get_size(edge[i].v) > N >> 1) return false;
	}
	return true;
}

int random_find(int rt) {
	intl N = 0;
	for (int i = 1; i <= t; i++) N += sum[inter[i].second] - sum[inter[i].first - 1];	
	int u = Random();
	if (u == 0) { printf("hehe"); exit(0); }	
	int t = 19; int v = rt;
	if (N - get_size(u) <= N / 2LL) v = u;
	else {
		for (; t >= 0; u = st[u][t]) {
			for (; t >= 0 && (!st[u][t] || pos[st[u][t]] < pos[rt]); t--);
			while (t >= 0 && (N - get_size(st[u][t]) <= N / 2LL)) v = st[u][t--];
		}
	}
	u = v;
	if (N - get_size(u) > N / 2LL) return INF;
	int ans = INF;
	if (check(u,N)) ans = u;
	u = st[u][0];
	if (pos[u] >= pos[rt] && (N - get_size(u) <= N / 2LL)) {
		if (check(u,N) && u < ans) ans = u;
	}
	return ans;
}

int solve(int p) {
	tp = 0;
	for (int i = 1; i <= m; i++) {
		if (pos[cuts[i]] > pos[cuts[p]] && end_pos[cuts[i]] <= end_pos[cuts[p]]) {
			if (tp && pos[cuts[i]] > pos[now[tp]] && end_pos[cuts[i]] <= end_pos[now[tp]]) continue;
			now[++tp] = cuts[i];
		}
	}
	int pas = pos[cuts[p]];
	sort(now + 1,now + tp + 1,cmp);
	t = 0;
	for (int i = 1; i <= tp; i++) {
		if (pas <= pos[now[i]] - 1)
			inter[++t] = make_pair(pas,pos[now[i]] - 1);
		pas = end_pos[now[i]] + 1;
	}
	if (pas <= end_pos[cuts[p]])
	inter[++t] = make_pair(pas,end_pos[cuts[p]]);
	int ans = INF;
	for (int T = 40; T; T--) {
		ans = min(ans,random_find(cuts[p]));
	}
	return ans;
}

int main() {
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	scanf("%d %d",&n,&q);
	for (int i = 1; i <= n; i++) scanf("%lld",&w[i]);
	for (int i = 1; i < n; i++) {
		scanf("%d %d",&A[i],&B[i]);
		make_edge(A[i],B[i]);	
	}
	dfs(1);
	for (int i = 1; i < n; i++)
		if (st[B[i]][0] == A[i]) swap(A[i],B[i]);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + w[sou[i]];
	prepare();
	for (; q; q--) {
		scanf("%d",&m);
		for (int i = 1; i <= m; i++) scanf("%d",&cuts[i]), cuts[i] = A[cuts[i]];
		cuts[++m] = 1;
		sort(cuts + 1,cuts + m + 1,cmp);
		for (int i = 1; i <= m; i++) ans[i] = solve(i);
		sort(ans + 1,ans + m + 1);
		for (int i = 1; i <= m; i++) printf("%d ",ans[i]);
		putchar('\n');
	}
	return 0;
}
