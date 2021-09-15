#include <bits/stdc++.h>
//#define ACM_LOCAL
using namespace std;
const int N = 5e4 + 10;

inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9') { if (ch == '-')w = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}

int pos[N], a[N], vis[2 * N]; 
int n, q, num, k;
long long res, ans[N];

struct Q {
	int l, r, id;
}p[N];

bool cmp(Q x, Q y) {
	if (pos[x.l] == pos[y.l]) return x.r < y.r;
	else return pos[x.l] < pos[y.l];
}

void add(int x) {

}

void sub(int x) {

}

void solve() {
	n = read(), q = read(), k = read();
	for (int i = 1; i <= n; i++) a[i] = read();

	int siz = sqrt(n);
	for (int i = 1; i <= n; i++) pos[i] = i / siz;

	for (int i = 1; i <= q; i++) {
		p[i].l = read(), p[i].r = read();
		p[i].id = i;
	}
	sort(p + 1, p + q + 1, cmp);

	int l = 1, r = 0;
	for (int i = 1; i <= q; i++) {
		while (p[i].l < l) add(--l);
		while (p[i].r > r) add(++r);
		while (p[i].l > l) sub(l++);
		while (p[i].r < r) sub(r--);
		ans[p[i].id] = res;
	}
	for (int i = 1; i <= q; i++) {
		printf("%lld\n", ans[i]);
	}
}