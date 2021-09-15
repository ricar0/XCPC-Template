#include <bits/stdc++.h>
using namespace std;
const int N = 5000 + 5;
int dis[N], n, m, h[N], cnt, maxd1[N], maxd2[N], mv[N], st, r;

struct edge {
	int u, to, next, vi;
}e[N<<1];

void add(int u, int v, int w) {
	e[cnt].u = u;
	e[cnt].to = v;
	e[cnt].vi = w;
	e[cnt].next = h[u];
	h[u] = cnt++;
}

void dp(int u, int fa) {
	maxd1[u] = 0, maxd2[u] = 0;
	for (int i = h[u]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v == fa) continue;
		dp(v, u);
		int tmp = maxd1[v] + e[i].vi;
		if (tmp > maxd1[u]) maxd2[u] = maxd1[u], maxd1[u] = tmp, mv[u] = v;
		else if (tmp > maxd2[u]) maxd2[u] = tmp;
	}
	st = max(st, maxd1[u] + maxd2[u]);
}

void dfs(int u, int fa, int fr) {
	r = min(r, max(fr, maxd1[u]));
	for (int i = h[u]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v == fa) continue;
		if (mv[u] == v) dfs(v, u, max(fr + e[i].vi, maxd2[u] + e[i].vi));
		else dfs(v, u, max(maxd1[u] + e[i].vi, fr + e[i].vi));
	}
}

int main() {
	cin >> n;
	memset(h, -1, sizeof h);
	for (int i = 1; i <= n - 1; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		add(x, y, z), add(y, x, z);
	}
	dp(1, 0);
	r = 0x3f3f3f3f;
	dfs(1, 0, 0);
	cout << r << endl;
}