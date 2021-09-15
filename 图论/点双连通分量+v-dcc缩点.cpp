#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int dfn[N], low[N], idx, cut[N], cnt, stk[N], tp;
vector<int> g[N], dcc[N];
int n, m;
void tarjan(int u, int root) {
	dfn[u] = low[u] = ++idx;
	stk[++tp] = u;
	if (u == root && g[u].empty()) {
		dcc[++cnt].push_back(u);
		return;
	}
	int child = 0;
	for (auto v : g[u]) {
		if (!dfn[v]) {
			tarjan(v, root);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				child++;
				if (child > 1 || u != root) cut[u] = 1;
				cnt++;
				int y;
				while (y = stk[tp--]) {
					dcc[cnt].push_back(y);
					if (y == v) break;
				}
				dcc[cnt].push_back(u);
			}
		}
		else 
			low[u] = min(low[u], dfn[v]);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, i);
	for (int i = 1; i <= n; i++) {
		for (auto x : dcc[i]) cout << x << " ";
		cout << endl;
	}
}

/*
9 11
1 2
1 5
2 3
2 5
3 4
4 5
1 6
6 7
9 8
6 9
6 8
*/