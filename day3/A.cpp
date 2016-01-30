#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 201000
#define intl long long
using namespace std;

int n,m;
char A[maxn],B[maxn];
int g,f[maxn][4],fa[maxn];
intl x,y;

int gcd(int a,int b) { return b ? gcd(b, a % b) : a; }

int main() {
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%s%s",A,B);
	n = strlen(A); m = strlen(B);
	g = gcd(n,m);
	for (int i = 0; i < g; i++) {
		bool flag = true;
		for (int j = i; j != i || flag; j = (j + g) % m) {
			fa[j] = i;
			if (B[j] == 'R') f[i][0]++;
			if (B[j] == 'P') f[i][1]++;
			if (B[j] == 'S') f[i][2]++;
			flag = false;
		}
	}

	x = 0; y = 0;
	for (int i = 0; i < n; i++) {
		if (A[i] == 'R') x += (intl) f[i % g][2], y -= (intl) f[i % g][0];
		if (A[i] == 'P') x += (intl) f[i % g][0], y -= (intl) f[i % g][1];
		if (A[i] == 'S') x += (intl) f[i % g][1], y -= (intl) f[i % g][2];
	}
	y += (intl) n * (intl) m / (intl) g - x;
	if (x > y) printf("TankEngineer");
	else if (x < y) printf("AngryBacon");
	else printf("Rowdark");
	return 0;
}
