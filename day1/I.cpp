#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>
#define intl long long
using namespace std;

intl T[2010000];
int nex[2010000],val[2010000],fst[2010000];
int n,m,d[40][40],e;
const int Mo = 1000000007;

int find(intl t) {
	int k = t % 1000007LL;
	for (int i = fst[k]; i; i = nex[i]) {
		if (T[i] == t) return val[i];
	}
	return -1;
}

void add(intl t,int val_) {
	int k = t % 1000007LL;
	nex[++e] = fst[k]; fst[k] = e; val[e] = val_; T[e] = t;	
	return;
}

int dp(intl t) {
	int k = 0;
	if (!t) return 1;	
	else if ((k = find(t)) != -1) return k;
	int ans = 0;
	for (k = 0; !(t >> k & 1LL); k++);
	for (int i = k + 1; i < n; i++) {
		if (!(t >> i & 1LL)) continue;
		if (!d[k + 1][i + 1]) continue;
		ans += dp(t ^ (1LL << k) ^ (1LL << i));
		if (ans >= Mo) ans -= Mo;
	}
	add(t,ans);
	return ans;
}

int main() {
	freopen("I.in","r",stdin);
	freopen("I.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= m; i++) {
		int a,b;
		scanf("%d %d",&a,&b);
		d[a][b] = d[b][a] = 1;
	}
	cout << dp((1LL << n) - 1LL) << endl;
	//printf("%d\n",e);
	return 0;
}
