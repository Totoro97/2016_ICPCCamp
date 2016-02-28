#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#define maxn 201000
#define intl long long
using namespace std;

struct str { intl a,b; } dot[maxn];
int n;
intl ans;

struct cmp {
	bool operator () (int a,int b) {
		return (dot[a].b < dot[b].b || (dot[a].b == dot[b].b && (a < b)));
	}
};
	
set <int,cmp> st;

bool pmc(const str &a, const str &b) {
	return (a.a > b.a || ((a.a == b.a) && (a.b > b.b)));
}

int main() {
	freopen("D.in","r",stdin);
	freopen("D.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%lld",&dot[i].a);
	for (int i = 1; i <= n; i++) scanf("%lld",&dot[i].b);
	sort(dot + 1,dot + n + 1,pmc);

	ans = 0;
	for (int i = 1; i <= n; i++) {
		if (i & 1) {
			if (st.empty()) continue;
			int k = *st.begin();
			if (dot[k].b < dot[i].b) {
				ans += dot[i].b - dot[k].b;
				st.erase(k); st.insert(i);
			} else continue;
		} else {
			ans += dot[i].b;
			st.insert(i);
		}
	}
	printf("%lld",ans);
	return 0;
}
