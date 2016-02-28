#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

map <int,int> st;
typedef map <int,int> :: iterator poi;
struct str { int a,c; } dot[310];
int n,ans;

bool check() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (dot[i].c != dot[j].c) return false;
	return true;
}

bool judge(int M) {
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			if (dot[i].c == dot[j].c && dot[i].a / M != dot[j].a / M) return false;
			if (dot[i].c != dot[j].c && dot[i].a / M == dot[j].a / M) return false;
		}
	return true;
}

int main() {
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d %d",&dot[i].a,&dot[i].c);
	for (int i = 1; i <= n; i++) dot[i].a--;
	if (check()) { printf("-1"); return 0; }
	for (int i = 1; i <= n; i++) {
		for (int u = 1; u <= dot[i].a;) {
			st[u] = 1; int k = 30;
			while (true) {
				while (k >= 0 && u + (1 << k) > dot[i].a) k--;
				while (k >= 0 && dot[i].a / u != dot[i].a / (u + (1 << k))) k--;
				if (k == -1) break;
				u += (1 << k);
			}
			u = u + 1;
			if (u == dot[i].a + 1) st[u] = 1;
		}
	}
	int pas = 0; bool flag = false;
	for (poi i = st.begin(); i != st.end(); i++) {
		if (flag) ans += i -> first - pas;
		flag = false;
		if (judge(i -> first)) flag = true;
		pas = i -> first;
	}
	printf("%d",ans);
	return 0;
}
