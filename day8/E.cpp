#include <cstdio>
#include <cstring>
#include <algorithm>
#define intl long long
#define maxn 1010
using namespace std;
intl A[maxn];
int n,m,ans;
intl sum;
int main() {
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%lld",&A[i]);
	sort(A + 1,A + n + 1);
	for (int i = 1; i <= n; i++) {
		if (sum < A[i]) {
			ans++;
			sum += A[i];
		}
	}
	printf("%d",ans);
	return 0;
}
