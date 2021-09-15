#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> query[N], query_id[N];

struct edge {
	int to, next, vi;
}e[N*2];

int T, n, q, h[N], cnt, ans[N], d[N], fa[N], vis[N];

void add_query(int u, int v, int id) {
	query[u].push_back(v), query_id[u].push_back(id);
	query[v].push_back(u), query_id[v].push_back(id);
}

void add(int u, int v, int w) {
	e[cnt].to = v;
	e[cnt].vi = w;
	e[cnt].next = h[u];
	h[u] = cnt++;
}

int find(int x) {
	if (fa[x] == x) return x;
	else return fa[x] = find(fa[x]);
}

void tarjan(int x) {
	vis[x] = 1;
	for (int i = h[x]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (vis[v]) continue;
		d[v] = d[x] + e[i].vi;
		tarjan(v);
		fa[v] = x;
	}

	for (int i = 0; i < query[x].size(); i++) {
		int y = query[x][i], id = query_id[x][i];
		if (vis[y] == 2) {
			int lca = find(y);
			ans[id] = min(ans[id], d[x] + d[y] - 2 * d[lca]);
		}
	}
	vis[x] = 2;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &q);
		for (int i = 1; i <= n; i++) {
			h[i] = -1;
			d[i] = 0;
			query[i].clear(), query_id[i].clear();
			fa[i] = i;
			vis[i] = 0;
		}
		cnt = 0;
		for (int i = 1; i <= n - 1; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			add(x, y, z), add(y, x, z);
		}
		for (int i = 1; i <= q; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			if (x == y) ans[i] = 0;
			else {
				add_query(x, y, i);
				ans[i] = 999999999;
			}
		}
		tarjan(1);
		for (int i = 1; i <= q; i++) {
			printf("%d\n", ans[i]);
		}
	}
}