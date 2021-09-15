#include<bits/stdc++.h>
using namespace std;
const int N = 100010;
int dfn[N], low[N], idx;
int n, m, ans;
vector<int> g[N];
void tarjan(int u, int fa) {
	dfn[u] = low[u] = ++idx;
	for (auto v : g[u]) {
        if(v == fa) continue;
 		if (!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) ans++;
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
	
	tarjan(1, 0);
	cout << m - ans;
}