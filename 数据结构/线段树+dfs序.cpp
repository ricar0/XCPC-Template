#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e4 + 10;
vector<int>g[maxn];
int a[maxn], b[maxn], cnt;
int in[maxn], out[maxn];
int tot, op[maxn];

struct SegmentTree {
	int l, r;
	int sum, tag;
	void upd(int v) {
		sum += (r - l + 1) * v;
		tag += v;
	}
}t[maxn << 2];

void dfs(int u) {
	in[u] = ++tot;
	for (auto i : g[u]) {
		dfs(i);
	}
	out[u] = tot;
}
void push_up(int u) {
	t[u].sum = t[u << 1].sum + t[u << 1 | 1].sum;
}

void pushdown(int rt) {
	if (t[rt].tag) {
		t[rt << 1].upd(t[rt].tag);
		t[rt << 1 | 1].upd(t[rt].tag);
		t[rt].tag = 0;
	}
}

void build(int l, int r, int u) {
	t[u].l = l, t[u].r = r;
	if (l == r) {
		t[u].sum = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, u << 1);
	build(mid + 1, r, u << 1 | 1);
	push_up(u);
}

void update(int L, int R, int c, int u) {
	if (L <= t[u].l && R >= t[u].r) {
		t[u].upd(c);
		return;
	}
	pushdown(u);
	int m = (t[u].l + t[u].r) >> 1;
	if (L <= m) update(L, R, c, u << 1);
	if (R > m) update(L, R, c, u << 1 | 1);
	push_up(u);
}

int query(int p, int u) {
	if (t[u].l == t[u].r) {
		return t[u].sum;
	}
	pushdown(u);
	int m = (t[u].l + t[u].r) >> 1;
	if (p <= m) return query(p, u << 1);
	else return query(p, u << 1 | 1);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n;
	cin >> n;
	int cnt = 1;
	for (int i = 1; i <= n; i++) {
		cin >> op[i] >> a[i];
		a[i]++;
		if (op[i] == 1) {
			cnt++; b[i] = cnt;
			g[a[i]].push_back(cnt);
		}
		else if (op[i] == 2) cin >> b[i];
	}
	dfs(1);
	build(1, tot, 1);
	for (int i = 1; i <= n; i++) {
		if (op[i] == 2) {
			update(in[a[i]], out[a[i]], b[i], 1);
		}
		else if (op[i] == 1) {
			int t = query(in[b[i]], 1);
			update(in[b[i]], in[b[i]], -t, 1);
		}
		else {
			cout << query(in[a[i]], 1) << endl;
		}
	}
	return 0;
}