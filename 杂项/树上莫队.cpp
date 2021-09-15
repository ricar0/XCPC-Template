#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
inline int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch>'9') { if (ch == '-')w = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') s = s * 10 + ch - '0', ch = getchar();
	return s * w;
}
int n, m;
struct edge {
	int to, next;
}e[N<<1];

struct Q {
	int l, r, id, lca;
}p[N];

int h[N], cnt, tot, in[N], out[N], a[N], b[N], pos[N], son[N], rnk[N], siz[N], top[N], d[N], fa[N], res, used[N], ans[N], vis[N];

void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = h[u];
	h[u] = cnt++;
}

bool cmp(Q x, Q y) {
	if (pos[x.l] == pos[y.l]) return x.r < y.r;
	else return pos[x.l] < pos[y.l];
}

void discrete() {
	sort(b + 1, b + n + 1);
	int num = unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + num + 1, a[i]) - b;
}

void dfs1(int u) {
	son[u] = -1;
	siz[u] = 1;
	in[u] = ++tot, rnk[tot] = u;
	for (int i = h[u]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (!d[v]) {
			d[v] = d[u] + 1;
			fa[v] = u;
			dfs1(v);
			siz[u] += siz[v];
			if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
		}
	}
	out[u] = ++tot, rnk[tot] = u;
}

void dfs2(int u, int t) {
	top[u] = t;
	if (son[u] == -1) return;
	dfs2(son[u], t);
	for (int i = h[u]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v != son[u] && v != fa[u]) dfs2(v, v);
	}
}

int lca(int u, int v) {
	while (top[u] != top[v]) {
		if (d[top[u]] > d[top[v]])
			u = fa[top[u]];
		else
			v = fa[top[v]];
	}
	return d[u] > d[v] ? v : u;
}

void Add(int x) {
	if (++vis[a[x]] == 1) ++res;
}

void Sub(int x) {
	if (--vis[a[x]] == 0) --res;
}

void ADD(int x) {
	used[x] ? Sub(x) : Add(x); 
	used[x] ^= 1;
}

int main() {
	n = read(), m = read();
	memset(h, -1, sizeof h);
	int siz = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = read(), b[i] = a[i];
	for (int i = 1; i <= 2 * n; i++) pos[i] = i / siz;
	discrete();
	for (int i = 1; i <= n - 1; i++) {
		int x, y;
		x = read(), y = read();
		add(x, y), add(y, x);
	}
	d[1] = 1;
	dfs1(1);
	dfs2(1, 1);
	for (int i = 1; i <= m; i++) {
		int x, y;
		x = read(), y = read();
		if (in[x] > in[y]) swap(x, y);
		int lca_ = lca(x, y);
		p[i].id = i;
		if (lca_ == x) p[i].l = in[x], p[i].r = in[y];
		else p[i].l = out[x], p[i].r = in[y], p[i].lca = lca_;
	}
	sort(p + 1, p + m + 1, cmp);

	int l = 1, r = 0;
	for (int i = 1; i <= m; i++) {
		while (p[i].l < l) ADD(rnk[--l]);
		while (p[i].r > r) ADD(rnk[++r]);
		while (p[i].l > l) ADD(rnk[l++]);
		while (p[i].r < r) ADD(rnk[r--]);
		if (p[i].lca) ADD(p[i].lca);
		ans[p[i].id] = res;
		if (p[i].lca) ADD(p[i].lca);
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}