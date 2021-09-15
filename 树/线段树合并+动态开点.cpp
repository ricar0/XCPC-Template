#pragma GCC optimize (2)
#include <bits/stdc++.h>
#define ACM_LOCAL
using namespace std;
const int N = 1e5 + 5;
const int M = 6e6 + 5;
struct edge {
    int to, next;
}e[2000010];

struct tree {
	int l, r;
	int maxx, id;
}t[M];

struct query {
	int x, y, z;
}q[N];

int tmp[N], n, m, h[N], cnt, son[N], root[N], siz[N], top[N], fa[N], tot, d[N], idx, all, ans[N], k;

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
		if (!d[v]) {
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

void push_up(int u) {
	int ls = t[u].l, rs = t[u].r;
	if (t[ls].maxx >= t[rs].maxx) t[u].maxx = t[ls].maxx, t[u].id = t[ls].id;
	else t[u].maxx = t[rs].maxx, t[u].id = t[rs].id;
}

void update(int &now, int l, int r, int pos, int val) {
	if (!now) now = ++idx;
	if (l == r && l == pos){
		t[now].maxx += val;
		t[now].id = l;
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid) update(t[now].l, l, mid, pos, val);
	else update(t[now].r, mid + 1, r, pos, val);
	push_up(now);
}

void merge(int &x, int &y, int l, int r) {
	if (!x) return;
	if (!y) { y = x;return; }
	if (l == r) {
		t[y].maxx += t[x].maxx;
		return;
	}
	int mid = (l + r) >> 1;
	merge(t[x].l, t[y].l, l, mid);
	merge(t[x].r, t[y].r, mid + 1, r);
	push_up(y);
}

void dfs_merge(int u, int fa) {
	for (int i = h[u]; ~i; i = e[i].next) {
		int v = e[i].to;
		if (v == fa) continue;
		dfs_merge(v, u);
		merge(root[v], root[u], 1, k);
	}
	if (t[root[u]].maxx == 0) ans[u] = 0;
	else {
		ans[u] = tmp[t[root[u]].id];
	}
}
void solve() {
	memset(h, -1, sizeof h);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n - 1; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		add(x, y), add(y, x);
	}
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &q[i].x, &q[i].y, &q[i].z);
		tmp[++k] = q[i].z;
	}
	d[1] = 1;
	dfs1(1);
	dfs2(1, 1);
	sort(tmp + 1, tmp + 1 + k);
	k = unique(tmp + 1, tmp + 1 + k) - (tmp + 1);
	for (int i = 1; i <= m; i++) {
		q[i].z = lower_bound(tmp + 1, tmp + 1 + k, q[i].z) - tmp;
		update(root[q[i].x], 1, k, q[i].z, 1);
		update(root[q[i].y], 1, k, q[i].z, 1);
		update(root[lca(q[i].x, q[i].y)], 1, k, q[i].z, -1);
		if (fa[lca(q[i].x, q[i].y)]) update(root[fa[lca(q[i].x, q[i].y)]], 1, k, q[i].z, -1);
	}
	dfs_merge(1, 0);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    signed test_index_for_debug = 1;
    char acm_local_for_debug = 0;
    do {
        if (acm_local_for_debug == '$') exit(0);
        if (test_index_for_debug > 20)
            throw runtime_error("Check the stdin!!!");
        auto start_clock_for_debug = clock();
        solve();
        auto end_clock_for_debug = clock();
        cout << "Test " << test_index_for_debug << " successful" << endl;
        cerr << "Test " << test_index_for_debug++ << " Run Time: "
            << double(end_clock_for_debug - start_clock_for_debug) / CLOCKS_PER_SEC << "s" << endl;
        cout << "--------------------------------------------------" << endl;
    } while (cin >> acm_local_for_debug && cin.putback(acm_local_for_debug));
#else
    solve();
#endif
    return 0;
}