#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
#include <sys/timeb.h>
#define R(a) ((abs(rand() * rand() + rand()) % (a)) + 1)
using namespace std;

double a[1000];
int T,n;

double Rand() {
	int a = R(100000001) - 1;
	return ((double) a / 100000000.0);
}

int main() {
	freopen("H.out","w",stdout);
	double x = 1;
	for (int i = 1; i <= 100; i++) x *= (double) 10.0;
	printf("%lf\n",x);
	return 0;
	T = 10000000; double ans = 0;
	n = 9;
	struct timeb t; ftime(&t); srand(t.millitm + t.time * 10000);
	for (int i = 1; i <= T; i++) {
		for (int j = 1; j <= n; j++) a[j] = Rand();
		sort(a + 1,a + n + 1); a[n + 1] = 1;
		double js = 1;
		for (int j = 1; j <= n + 1; j++) js = min(js,a[j] - a[j - 1]);
		ans += js;
	}	
	printf("%.12lf\n",ans / (double) T);
	return 0;
}
