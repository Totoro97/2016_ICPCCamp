#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int pri[1010000],mark[1010000];
int top,k;
int N = 10000;
int n;
int main() {
	freopen("G.in","r",stdin);
	freopen("G.out","w",stdout);
	scanf("%d",&k);  
	for (int i = 2; i <= N; i++) {
		if (!mark[i]) { pri[++top] = i; }
		for (int j = 2; j <= N && i * j <= N; j++)
			mark[i * j] = 1;		
	}
	//for (int i = 1; i <= top; i++) printf("%d\n",pri[i]);
	n = pri[920];
	printf("%d\n",n);
	for (int i = 920 - 1; i >= 920 - k; i--) {
		bool flag = false;
		for (int u = 1; !flag || u != 1; u = ((u - 1) + pri[i]) % n + 1) {
			if (((u - 1) + pri[i]) % n + 1 != 1)
				printf("%d %d\n",u,((u - 1)+ pri[i]) % n + 1);
			flag = true;
		}
	}
	return 0;
}
