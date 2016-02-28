#include <cstdio>
#include <cstring>
#include <algorithm>
#define intl long long
#define Pair pair<intl,intl>
#define maxn 1001000
#define base 1000000000LL
using namespace std;

intl pa[maxn],pb[maxn],mu[maxn],zi[maxn],A[maxn],B[maxn];
intl Z,M,Mo;
int N_,n,m,flag,ta,tb,tz,tm,T,N;
int pr[5001000],mark[5001000],top;

const intl pri[20] = { 2,3,5,7,11,13,17,19,23,29,31,37 };

intl gcd(intl a,intl b) { return b? gcd(b,a % b) : a; }

Pair ex_gcd(intl a,intl b) {
	if (!b) { return make_pair(1LL,0LL); }
	intl x,y;
	Pair wp = ex_gcd(b, a % b);
	x = wp.second;
	//intl a1 = 0, a2 = 0, a3 = 0, a4 = 0;
	y = wp.first - (a / b) * wp.second;
	return make_pair(x,y);
}

struct bignum {
	intl v[5];
	void set(intl a) {
		for (int i = 1; i <= 4; i++) v[i] = 0;
		v[1] = a;
		for (int i = 2; i <= 4; i++) v[i] += v[i - 1] / base, v[i] %= base;	   
 	}

	void operator *= (bignum b){
		intl v_[5];
		for (int i = 1; i <= 4; i++) v_[i] = v[i], v[i] = 0;
		for (int i = 1; i <= 3; i++)
			for (int j = 1; j <= 3; j++)
				v[i + j - 1] += v_[i] * b.v[j];
		for (int i = 1; i <= 3; i++)
			v[i] += v[i] / base, v[i] %= base;
	}
} a_,b_;
	
intl product_mod(intl x,intl y,intl n) {
	/*intl wp = 1;
	if (x < 0LL) wp = -wp, x = -x;
	if (y < 0LL) wp = -wp, y = -y;
	a_.set(x); b_.set(y);
	a_ *= b_;
	intl ans = 0;
	for (int i = 4; i >= 1; i--) ans = (ans * base + a_.v[i]) % n;
	return ans * wp;*/
	intl wp;
	if (y < 0) wp = -1LL, y = -y;
	else wp = 1LL;
	intl s=0,t=x;
	for (;y;y>>=1){
		if (y&1)s=(s+t)%n;
		t=t*2%n;
	}
	return s * wp;
}

intl power_mod(intl x,intl y,intl n){
	x%=n;
	intl s=1,t=x;
	for (;y;y>>=1){
		if (y&1)s=product_mod(s,t,n);
		t=product_mod(t,t,n);
	}
	return s;
}

bool Miintler_Rabin(intl N){
	if (N < 2) return false;
	if (N == 2)return true;
	if (!(N&1))return false;
	if (N <= N_ && !mark[N]) return true;
	intl m,k=0,a;
	m=N-1;
	while (!(m&1))k++,m=m/2;
	for (intl i=0; i < 10; i++) {
		if (pri[i]>=N)break;
		a=power_mod(pri[i],m,N);
		if (a==1)continue;
		intl j;
		for (j=0;j<k;j++){
			if (a==N-1)break;
			a=product_mod(a,a,N);
		}
		if (j==k)return false;
	}
	return true;
}

intl pointlard_rho(intl C,intl N){
	intl i,k,x1,x2,d;
	i=1;k=2;
	x1=x2=rand()%N;
	do{
		i++;
		d=gcd(x2-x1+N,N);
		if (d>1&&d<N)return d;
		if (i==k)k=k<<1,x2=x1;
		x1=(product_mod(x1,x1,N)+N-C)%N;
	}while (x1!=x2);
	return N;
}

void rho(intl N,intl *q,int &las) {
	if (N<2)return;
	if (Miintler_Rabin(N)){q[++las]=N;return;}
	intl T;
	do{
		T=pointlard_rho(rand()%(N-1)+1,N);
	}while (T==N);
	rho(N/T,q,las);
	rho(T,q,las);
}

int main() {
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	scanf("%d %d",&n,&m);
	N_ = N = 5000000;
	
	for (int i = 1; i <= N; i++) {
		if (!mark[i]) pr[++top] = i;
		for (int j = 1; j <= top && pr[j] * i <= N; j++) {
			mark[i * pr[j]] = 1;
			if (!(i % pr[j])) break;
		}
	}

	for (int i = 1; i <= n; i++) scanf("%lld",&A[i]);
	for (int i = 1; i <= m; i++) scanf("%lld",&B[i]);
	for (int i = 1; i <= n; i++) rho(A[i],pa,ta);
	for (int i = 1; i <= m; i++) rho(B[i],pb,tb);
	sort(pa + 1,pa + ta + 1);
	sort(pb + 1,pb + tb + 1);
	int a = 1,b = 1;
	while (a <= ta || b <= tb) {
		if (a > ta) mu[++tm] = pb[b++];
		else if (b > tb) zi[++tz] = pa[a++];
		else if (pa[a] == pb[b]) { a++; b++; }
		else if (pa[a] < pb[b]) zi[++tz] = pa[a++];
		else mu[++tm] = pb[b++];
	}
	for (scanf("%d",&T); T; T--) {
		scanf("%lld",&Mo);
		Z = 1LL;
		for (int i = 1; i <= tz; i++) Z = product_mod(Z,zi[i],Mo);
		flag = true;
		for (int i = 1; i <= tm; i++) if (gcd(mu[i],Mo) != 1LL) { flag = false; break; }
		if (!flag) {
			printf("DIVISION BY ZERO\n");
			continue;
		}
		for (int i = 1; i <= tm; i++)
			Z = product_mod(Z,ex_gcd(mu[i],Mo).first,Mo);
		(Z += Mo) %= Mo;
		printf("%lld\n",Z);
	}
	return 0;
}
