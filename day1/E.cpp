// 11:18
// 12:19
// 12:21 Wrong answer on #5
// 12:23 Wrong answer on #5
// 12:42 Tong Shang
// 12:48 Tong Shang

#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>
#define eps (1e-8)
#define maxn 1010000
#define Pair pair<int,int>

using namespace std;

const double INF = 1e14;

int sig(double a) { return a < -eps ? -1 : (a > eps); }

struct point {
	double x,y;
	point (double x = 0, double y = 0) : x(x) , y(y) {}
} dot[maxn];

point operator + (point a,point b) { return point(a.x + b.x, a.y + b.y); }
point operator - (point a,point b) { return point(a.x - b.x, a.y - b.y); }
point operator * (point a,double p) { return point(a.x * p,a.y * p); }
point operator / (point a,double p) { return point(a.x / p,a.y / p); }
double operator * (point a,point b) { return a.x * b.x + a.y * b.y; }
double operator / (point a,point b) { return a.x * b.y - a.y * b.x; } 

double length(point a) { return sqrt(a * a); }

struct Line {
	point v,p;
	int num;
} line[maxn];

point cross_line(Line a,Line b) {
	point u = a.p - b.p;
	if (!sig(a.v / b.v)) return point(INF,INF);
	double t = (b.v / u) / (a.v / b.v);
	return a.p + a.v * t;
}

vector <int> ban[maxn];

int sta[maxn],A[210],B[210];
int n,m,top;
double ans;

set <Pair> st;

bool cmp(const Line &a, const Line &b) {
	return (a.v / b.v > 0);
}

bool pmc(const Line &a, const Line &b) {
	return a.num < b.num;
}

void add_point(int u) {
	double Lval = INF, Rval = -INF;
	point L,R;
	int q = 0;
	for (int v = 1; v <= n; v++) {
		while (q < (int) ban[u].size() && ban[u][q] < v) q++;
		if (q < (int) ban[u].size() && ban[u][q] == v) continue;
		if (v == u) continue;
		point now = cross_line(line[u], line[v]);
		double js;
		if ((js = (now - line[u].p) * (line[u].v)) < Lval) {
			Lval = js;
			L = now;
		}
		if ((js = (now - line[u].p) * (line[u].v)) > Rval) {
			Rval = js;
			R = now;
		}
	}
	if (Lval <  INF / 2.0) dot[++top] = L;
	if (Rval > -INF / 2.0) dot[++top] = R;
}

bool dot_R(point a,point b) {
	return (a / b > eps);
}

bool wp(const point &a, const point &b) {
	if (a.x < b.x - eps) return true;
	else if (a.x > b.x + eps) return false;
	return a.y < b.y;
}

bool operator == (point a,point b) {
	return (!sig(a.x - b.x) && !sig(a.y - b.y));
}

void convex_hull() {
	sort(dot + 1,dot + top + 1,wp);
	n = top; top = 0;
	for (int i = 1; i <= n; i++) {
		if (i < n && dot[i] == dot[i + 1]) continue;
		while (top > 1 && dot_R(dot[i] - dot[sta[top]], dot[sta[top]] - dot[sta[top - 1]])) top--;
		sta[++top] = i;
	}
	for (int i = n - 1; i >= 1; i--) {
		if (i > 1 && dot[i] == dot[i - 1]) continue;
		while (top > 1 && dot_R(dot[i] - dot[sta[top]], dot[sta[top]] - dot[sta[top - 1]])) top--;
		sta[++top] = i;
	}
	ans = 0;
	for (int i = 2; i <= top; i++)
		ans += length(dot[sta[i]] - dot[sta[i - 1]]);	
}

int main() {
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; i++) {
		int a,b,c;
		scanf("%d %d %d",&a,&b,&c);
		if (a) line[i] = (Line) { point(b, -a), point((double) c / (double) a, 0), i };
		else line[i] = (Line) { point(b, -a), point(0, (double) c / (double) b), i };
		if (line[i].v.y < 0) line[i].v.x = -line[i].v.x, line[i].v.y = -line[i].v.y;
		if (!line[i].v.y && line[i].v.x < 0) line[i].v.x = -line[i].v.x;		
	}
	sort(line + 1,line + n + 1,cmp);
	line[n + 1] = line[1];
	for (int i = 1; i <= n; i++) {
		int a = line[i].num, b = line[i + 1].num;
		if (a > b) swap(a,b);
		st.insert(make_pair(a,b));
	}
	sort(line + 1,line + n + 1,pmc);
	for (int i = 1; i <= m; i++) scanf("%d %d",&A[i],&B[i]);
	for (int i = 1; i <= m; i++) {
		ban[A[i]].push_back(B[i]);
		ban[B[i]].push_back(A[i]);
	}
	for (int i = 1; i <= n; i++) sort(ban[i].begin(), ban[i].end());
	
 	for (int i = 1; i <= m; i++) {
		int a = A[i],b = B[i];
		if (a > b) swap(a,b);
		if (st.find(make_pair(a,b)) != st.end()) {
			st.erase(make_pair(a,b));
		}
		add_point(a); add_point(b);
	}
	
	for (set<Pair> :: iterator i = st.begin(); i != st.end(); i++) {
		dot[++top] = cross_line(line[i -> first],line[i -> second]);
	}
	
	convex_hull();
	printf("%.10lf",ans);
	return 0;
}
