#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;

struct edge {
	int to, next;
}e[N*2];

int t, n, m, h[N], cnt, d[N], vis[N], f[N][30], c[N], ff[N];

void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = h[u];
	h[u] = cnt++;
}

void bfs(int x) {
	queue<int> q;
	d[x] = 1;
	q.push(x);
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (int i = h[u]; ~i; i = e[i].next) {
			int v = e[i].to;
			if (d[v]) continue;
			d[v] = d[u] + 1;
			f[v][0] = u;
			for (int j = 1; j <= t; j++) {
				f[v][j] = f[f[v][j - 1]][j - 1];
			}
			q.push(v);
		}
	}
}

int lca(int x, int y) {
	if (d[x] > d[y]) swap(x, y);
	for (int i = t; i >= 0; i--) if (d[f[y][i]] >= d[x]) y = f[y][i];

	if (x == y) return x;
	for (int i = t; i >= 0; i--) {
		if (f[x][i] != f[y][i]) {
			x = f[x][i], y = f[y][i];
		}
	}
	return f[x][0];
}

void dfs(int x, int fa) {
	for (int i = h[x]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v == fa) continue;
		dfs(v, x);
		c[x] += c[v];
	}
}

int main() {
	memset(h, -1, sizeof h);
	scanf("%d %d", &n, &m);
	t = (int)(log(n) / log(2)) + 1;
	for (int i = 1; i <= n - 1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		add(x, y), add(y, x);
	}
	bfs(1);
	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		c[x] ++, c[y] ++;
		c[lca(x, y)] -= 2;
	}
	dfs(1, 0);
	int res = 0;
	for (int i = 2; i <= n; i++) {
		if (!c[i]) res += m;
		else if (c[i] == 1) res++;
	}
	printf("%d", res);
}