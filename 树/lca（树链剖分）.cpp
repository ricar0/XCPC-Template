#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;

struct edge {
	int to, next;
}e[N*2];

int tot, h[N], cnt, n, m, son[N], d[N], fa[N], siz[N], dfn[N], rnk[N], top[N];

void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = h[u];
	h[u] = cnt++;
}

void dfs1(int u) {
	son[u] = -1;
	siz[u] = 1;
	for (int i = h[u]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (!siz[v]) {
			d[v] = d[u] + 1;
			fa[v] = u;
			dfs1(v);
			siz[u] += siz[v];
			if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
		}
	}
}

void dfs2(int u, int t) {
	top[u] = t;
	dfn[u] = ++tot;
	rnk[tot] = u;
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

int main() {
	ios::sync_with_stdio(0);
	int r;
	memset(h, -1, sizeof h);
	cin >> n >> m >> r;
	for (int i = 1; i <= n - 1; i++) {
		int x, y;
		cin >> x >> y;
		add(x, y), add(y, x);
	}
	d[r] = 1;
	dfs1(r);
	dfs2(r, r);
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		printf("%d\n", lca(x, y));
	}
}