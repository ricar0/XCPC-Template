#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int M = 2e5 + 10;

struct edge {
	int to, next;
}e[M<<1];

int n, m, t, stk[N], tp, cnt, h[N], vis[M<<1], ans[N];

void add(int u, int v) {
	e[cnt].to = v;
	e[cnt].next = h[u];
	h[u] = cnt++;
}

void euler() {
	stk[++tp] = 1;
	while (tp > 0) {
		int x = stk[tp], i = h[x];
		while (i && vis[i]) i = e[i].next;
		if (i) {
			stk[++tp] = e[i].to;
			vis[i] = vis[i ^ 1] = 1;
			h[x] = e[i].next;
		}
		else {
			tp--;
			ans[++t] = x;
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		add(x, y), add(y, x);
	}
	euler();
	for (int i = t; i >= 1; i--) cout << ans[i] << " ";
}

/*
7 9
1 2
1 3
1 4
1 5
2 3
4 5
5 6
6 7
5 7
*/