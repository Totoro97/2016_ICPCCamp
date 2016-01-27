#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 201000
using namespace std;

const int Mo = 1000000007LL;
int f[1 << 16];
int A[maxn],n,m,d;
int now,ans;

int find(int A,int k) {
	if (k >= d) return f[A];
	if ((A >> k) & 1) return (find(A,k + 1) + find(A ^ (1 << k),k + 1)) % Mo;
	else return find(A,k + 1);
}

void add(int A,int k,int val) {
	if (k > m) {
		f[A] += val, f[A] %= Mo;
		return;
	}
	if ((A >> k) & 1) add(A,k + 1,val);
	else {
		add(A,k + 1,val);
		add(A + (1 << k),k + 1,val);
	}
}

int main() {
	freopen("F.in","r",stdin);
	freopen("F.out","w",stdout);
	scanf("%d %d",&n,&d);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < d; j++) {
			char ch;
			do ch = getchar(); while (ch != '0' && ch != '1');
			if (ch == '1') A[i] += (1 << j);
		}
	}
	
    m = d >> 1;	
	for (int i = 1; i <= n; i++) {
		now = find(A[i],m + 1);
		ans += now + 1; ans %= Mo;
		add(A[i],0,now + 1);
	}
	printf("%d",ans);
	return 0;
}
