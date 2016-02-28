#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define intl long long
using namespace std;
int A[101000];
int n,sum;
intl ans;
const intl Mo = 1000000007LL;
intl C(intl a,int b) {
	if (b == 0) return 1LL;
	if (b == 1) return a;
	return (a * (a - 1LL) / 2LL) % Mo;
}

int main() {
	freopen("J.in","r",stdin);
	freopen("J.out","w",stdout);
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d",&A[i]), sum += A[i];
	if (sum != 2 * n - 2) {
		printf("0");
		return 0;
	}
	if (n == 1 || n == 2) { printf("1"); return 0; }
	ans = 1LL; int k = n - 2;
	for (int i = 1; i <= n; i++) {
		ans *= C(k,A[i] - 1), ans %= Mo;
		k -= (A[i] - 1);
	}
	cout << ans << endl;
	return 0;
}
