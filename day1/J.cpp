//18:13
//18:47 Wrong answer on #14
//18:55 Wrong answer on #17
//19:07 Wrong answer on #17
//19:55 Wrong answer on #17
//19:55 Accepted
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define intl long long
#define maxn 2010
using namespace std;

int sum[maxn][maxn],A[maxn];
int n,m,p[10];
int x,y;
intl ans;

bool judge(int a,int b) {
	int x = 1, y = 1;
	for (; x == a || x == b; x++);
	for (; y == a || y == b || y == x; y++);
	int p1, p2;
	if (x < a) p1 = 0; else if (x > b) p1 = 2; else p1 = 1;
	if (y < a) p2 = 0; else if (y > b) p2 = 2; else p2 = 1;
	if (p1 == p2) return false;
	int A = min(p[a],p[b]), B = max(p[a],p[b]);
	if (p[x] < A) p1 = 0; else if (p[x] > B) p1 = 2; else p1 = 1;
	if (p[y] < A) p2 = 0; else if (p[y] > B) p2 = 2; else p2 = 1;
	if (p1 == p2) return false;
	return true;
}

void proc(int &x,int &y) {
	for (x = 1; x <= 4; x++)
		for (y = x + 1; y <= 4; y++) {
			if (judge(x,y)) return;
		}
	x = 0; y = 0; return;
}

void prepare() {
	for (int i = 1; i <= n; i++) sum[i][A[i]] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	return;
}

int get_sum(int k,int u,int l,int r,int L,int R) {
	L = A[L]; R = A[R];
	if (L > R) swap(L, R);
	if (l > r) swap(l, r);
	if (u < l) return sum[k][L - 1];
	else if (u > r) return sum[k][n] - sum[k][R];
	else return sum[k][R - 1] - sum[k][L];
}

intl solve_1_3() {
	intl ans = 0;
	for (int L = 1; L <= n; L++)
		for (int R = L + 1; R <= n; R++) {
			if ((p[1] < p[3]) ^ (A[L] < A[R])) continue;
			int a = get_sum(R - 1,p[2],p[1],p[3],L,R) - get_sum(L,p[2],p[1],p[3],L,R); 
			int b = get_sum(n,p[4],p[1],p[3],L,R) - get_sum(R,p[4],p[1],p[3],L,R);
			ans += (intl) (a * b);
		}
	return ans;
}

intl solve_2_4() {
	intl ans = 0;
	for (int L = 1; L <= n; L++)
		for (int R = L + 1; R <= n; R++) {
			if ((p[2] < p[4]) ^ (A[L] < A[R])) continue;
			int a = get_sum(L - 1,p[1],p[2],p[4],L,R);
			int b = get_sum(R - 1,p[3],p[2],p[4],L,R) - get_sum(L,p[3],p[2],p[4],L,R);
			ans += (intl) (a * b);
		}
	return ans;
}

intl solve_2_3() {
	intl ans = 0;
	for (int L = 1; L <= n; L++)
		for (int R = L + 1; R <= n; R++) {
			if ((p[2] < p[3]) ^ (A[L] < A[R])) continue;
			int a = get_sum(L - 1,p[1],p[2],p[3],L,R);
			int b = get_sum(n,p[4],p[2],p[3],L,R) - get_sum(R,p[4],p[2],p[3],L,R);
			ans += (intl) (a * b);
		}
	return ans;
}

void solve() {
	if (x == 1 && y == 3) ans = solve_1_3();
	else if (x == 2 && y == 4) ans = solve_2_4();
	else if (x == 2 && y == 3) ans = solve_2_3();
	else { printf("woc!"); return; }	
}

void special() {
	if (p[1] == 3) {
		for (int i = 1; i <= 4; i++) p[i] = 5 - p[i];
		for (int i = 1; i <= n; i++) A[i] = n + 1 - A[i];
		memset(sum,0,sizeof(sum));
		for (int i = 1; i <= n; i++) sum[i][A[i]] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
	}
	ans = solve_2_3();
	swap(p[1],p[4]);
	ans -= solve_1_3();
}

int main() {
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= 4; i++) scanf("%d",&p[i]);
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]);
	prepare();
	proc(x,y);
	if (x) solve();
	else special();
	cout << ans << endl;
	return 0;
}
