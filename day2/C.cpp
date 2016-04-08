#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define intl long long
#define Pair pair<int,intl>
using namespace std;

intl x_valid[4][40100],y_valid[4][40100];
intl ans,Ax[4][80100],Ay[4][80100];
intl A[40],C[4010][4010];
int x_sz[100],y_sz[100];
int n,a,b,c,m,x[20100],y[20100],X[20100],Y[20100];

const intl Mo = 1000000007LL;

intl prepare(int *x, int n,int u,int m) {
	intl ans = 1LL;
	for (int i = 0; i < n; i++) {
		int k = abs(x[i] - u);
		if ((m + k) & 1) return 0;
		if (k > m) return 0;
		ans *= C[m][(m + k) / 2];
		ans %= Mo;
	}
	return ans;
}

//int main() __attribute__((optimize("-O2")));

int main() {
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	C[0][0] = 1LL;
	
	for (int i = 1; i <= 2000; i++) {
		C[i][0] = 1LL;
		for (int j = 1; j <= i; j++)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % Mo;
	}
	
	while (scanf("%d %d %d %d",&n,&a,&b,&m) != EOF) {
		for (int i = 1; i <= n; i++) {
			int x_,y_;			
			scanf("%d %d",&x_,&y_);
			x[i] = x_ + y_; y[i] = x_ - y_;			
			x[i] += 4000; y[i] += 4000;
		}
		
		c = n - a - b;
		memset(Ax,0,sizeof(Ax));
		memset(Ay,0,sizeof(Ay));

		
		memset(x_sz,0,sizeof(x_sz));
		memset(y_sz,0,sizeof(y_sz));
		
		for (int i = (x[1] + m) & 1; i <= 8000; i += 2) Ax[1][i] = prepare(x + 1,a,i,m);
		for (int i = (y[1] + m) & 1; i <= 8000; i += 2) Ay[1][i] = prepare(y + 1,a,i,m);
		for (int i = (x[a + 1] + m) & 1; i <= 8000; i += 2) Ax[2][i] = prepare(x + a + 1,b,i,m);
		for (int i = (y[a + 1] + m) & 1; i <= 8000; i += 2) Ay[2][i] = prepare(y + a + 1,b,i,m);
		for (int i = ((x[a + b + 1] + m) & 1); i <= 8000; i += 2) Ax[3][i] = prepare(x + a + b + 1,c,i,m);
		for (int i = ((y[a + b + 1] + m) & 1); i <= 8000; i += 2) Ay[3][i] = prepare(y + a + b + 1,c,i,m);

		for (int i = 0; i <= 8000; i++) {
			for (int t = 1; t <= 3; t++) {
				if (Ax[t][i]) x_valid[t][++x_sz[t]] = Ax[t][i];
				if (Ay[t][i]) y_valid[t][++y_sz[t]] = Ay[t][i];			
			}
		}
		
		A[1] = A[2] = A[3] = 0;
		
		for (int t = 1; t <= 3; t++) {
			intl w = 0, p = 0;
			for (int i = 1; i <= x_sz[t]; i++) w += x_valid[t][i], w %= Mo;
			for (int i = 1; i <= y_sz[t]; i++) p += y_valid[t][i], p %= Mo;
			A[t] = w * p % Mo;
		}

		ans = A[1] * A[2] % Mo * A[3] % Mo;

		memset(Ax,0,sizeof(Ax));
		memset(Ay,0,sizeof(Ay));
		
		for (int i = (x[1] + m) & 1; i <= 8000; i += 2) Ax[1][i] = prepare(x + 1,a + b,i,m);
		for (int i = (y[1] + m) & 1; i <= 8000; i += 2) Ay[1][i] = prepare(y + 1,a + b,i,m);
		for (int i = (x[a + 1] + m) & 1; i <= 8000; i += 2) Ax[2][i] = prepare(x + a + 1,b + c,i,m);
		for (int i = (y[a + 1] + m) & 1; i <= 8000; i += 2) Ay[2][i] = prepare(y + a + 1,b + c,i,m);
		memcpy(X,x,sizeof(x)); memcpy(Y,y,sizeof(y));
		for (int i = a + 1; i + b <= n; i++) x[i] = x[i + b], y[i] = y[i + b];
		for (int i = (x[1] + m) & 1; i <= 8000; i += 2) Ax[3][i] = prepare(x + 1,a + c,i,m);
		for (int i = (y[1] + m) & 1; i <= 8000; i += 2) Ay[3][i] = prepare(y + 1,a + c,i,m);

		memset(x_sz,0,sizeof(x_sz));
		memset(y_sz,0,sizeof(y_sz));
		
		for (int i = 0; i <= 8000; i++) {
			for (int t = 1; t <= 3; t++) {
				if (Ax[t][i]) x_valid[t][++x_sz[t]] = Ax[t][i];
				if (Ay[t][i]) y_valid[t][++y_sz[t]] = Ay[t][i];			
			}
		}

		for (int t = 1; t <= 3; t++) {
			int k;
			if (t == 1) k = 3;
			else if (t == 2) k = 1;
			else k = 2;
			intl w = 0, p = 0;
			for (int i = 1; i <= x_sz[t]; i++) w += x_valid[t][i], w %= Mo;
			for (int i = 1; i <= y_sz[t]; i++) p += y_valid[t][i], p %= Mo;
			ans -= w * p % Mo * A[k]; ans %= Mo;
		}


		memset(Ax,0,sizeof(Ax));
		memset(Ay,0,sizeof(Ay));
		for (int i = (x[1] + m) & 1; i <= 8000; i += 2) Ax[1][i] = prepare(X + 1,n,i,m);
		for (int i = (y[1] + m) & 1; i <= 8000; i += 2) Ay[1][i] = prepare(Y + 1,n,i,m);

		memset(x_sz,0,sizeof(x_sz));
		memset(y_sz,0,sizeof(y_sz));
		
		for (int i = 0; i <= 8000; i++) {
			int t = 1;
			if (Ax[t][i]) x_valid[t][++x_sz[t]] = Ax[t][i];
			if (Ay[t][i]) y_valid[t][++y_sz[t]] = Ay[t][i];			
		}

		intl w = 0, p = 0;
		for (int i = 1; i <= x_sz[1]; i++) w += x_valid[1][i], w %= Mo;
		for (int i = 1; i <= y_sz[1]; i++) p += y_valid[1][i], p %= Mo;
		ans += w * p % Mo * 2LL; ans %= Mo;
		ans += Mo; ans %= Mo;
		cout << ans << endl;
	}
	return 0;
}
