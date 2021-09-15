#include <bits/stdc++.h>
#define ACM_LOCAL
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
const int N = 2e5 + 10;
const int M = 5e5 + 10;
const int MOD = 1e9 + 7;

struct Hash {
    int b[N], tot;
    void init() { tot = 0; }
    void insert(int x) { b[++tot] = x; }
    void build() {
        sort(b + 1, b + 1 + tot);
        tot = unique(b + 1, b + 1 + tot) - (b + 1);
    }
    int pos(int x) { return lower_bound(b + 1, b + 1 + tot, x) - b; }
} ha;
struct Edge {
    int u, v, w;
    bool operator < (const Edge &rhs) const {
        return w < rhs.w;
        // > 最大边中的最小值
        // < 最小边中的最大值
    }
} e[M];

int n, m, d[N], dfn[N], t, f[N][20], q, idx, rnk[N], in[N], out[N];
int cnt, val[N], fa[N], a[N];
int rt[N], NodeNum;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

vector<int> g[N];

void dfs(int x, int fa) {
    rnk[dfn[x] = ++idx] = x, f[x][0] = fa, d[x] = d[fa] + 1;
    for (int i = 1; i <= 19; i++) f[x][i] = f[f[x][i-1]][i-1];
    in[x] = idx;
    for (auto &y : g[x])
        if (y != fa) dfs(y, x);
    out[x] = idx;
}

void exKruskal() {
    cnt = n; for (int i = 1; i < (n << 1); i++) fa[i] = i;
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= m; i++) {
        int u = find(e[i].u), v = find(e[i].v);
        if (u == v) continue;
        val[++cnt] = e[i].w;
        fa[u] = fa[v] = cnt;
        g[u].push_back(cnt), g[cnt].push_back(u);
        g[v].push_back(cnt), g[cnt].push_back(v);
        if (cnt == (n << 1) - 1) break;//最多2N-1个点
    }
    for (int i = 1; i <= cnt; i++)
        if (!d[i]) {//未访问过
            int rt = find(i);//下树剖lca
            dfs(rt, 0);
        }
}
int FindPoint (int x, int p) {
    for (int i = 20; i >= 0; i--)
        if (d[x] > (1 << i) && val[f[x][i]] <= p) x = f[x][i];
    return x;
}

struct {
    int t[N << 5], lc[N << 5], rc[N << 5];
    int update(int pre, int l, int r, int x) {
        int num = ++NodeNum;
        lc[num] = lc[pre], rc[num] = rc[pre], t[num] = t[pre] + 1;
        if (l != r) {
            int mid = (l + r) >> 1;
            if (x <= mid) lc[num] = update(lc[pre], l, mid, x);
            else rc[num] = update(rc[pre], mid + 1, r, x);
        }
        return num;
    }
    int query(int pre, int now, int l, int r, int k) {
        if (t[now] - t[pre] < k) return -1;//如果之间的数少于k个，返回-1
        k = t[now] - t[pre] - k + 1;//这里主席树写的是第k小，转换一下变成第k大
        while (l < r) {
            int sum = t[lc[now]] - t[lc[pre]];
            if (k <= sum) {
                now = lc[now], pre = lc[pre];
                r = l + r >> 1;
            }
            else {
                now = rc[now], pre = rc[pre];
                l = (l + r >> 1) + 1;
                k -= sum;
            }
        }
        return ha.b[l];
    }
}hjt;

int ask(int x, int p, int k) {
    int pos = FindPoint(x, p);
    return hjt.query(rt[in[pos]-1], rt[out[pos]], 1, ha.tot, k);
}

void solve() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> a[i], ha.insert(a[i]);
    ha.build();
    for (int i = 1; i <= m; i++)
        cin >> e[i].u >> e[i].v >> e[i].w;
    exKruskal();
    for (int i = 1; i <= idx; i++) {
        rt[i] = rt[i-1];
        if (rnk[i] <= n)
            rt[i] = hjt.update(rt[i-1], 1, ha.tot, ha.pos(a[rnk[i]]));
    }

    while (q--) {
        int v, x, k;
        cin >> v >> x >> k;
        printf("%d\n", ask(v, x, k));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif
    solve();
}
