#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int dfn[N], low[N], idx;
vector<int> g[N];
set<int> st;
int n, m;
void tarjan(int u, int root, int fa) {
	dfn[u] = low[u] = ++idx;
	int child = 0;
	for (auto v : g[u]) {
		if (!dfn[v]) {
			tarjan(v, root, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u] && u != root) st.insert(u);
			if (u == root) child++;
		}
		else if(v != fa)
			low[u] = min(low[u], dfn[v]);
	}
	if (child >= 2 && u == root) st.insert(u);
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i, i, 0);

	cout << st.size() << endl;
	for (auto x : st) cout << x << " ";
}