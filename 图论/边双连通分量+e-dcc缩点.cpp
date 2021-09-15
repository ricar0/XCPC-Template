const int N = 5e5 + 10, M = 5e5 + 10, INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
int in[N];
int ans;
struct E_DCC {
    int dfn[N], low[N], bridge[M], h1[N], h2[N], belong[N];
    int cnt1, cnt2, idx, scc, num;
    struct Edge {
        int to, next;
    } e1[N << 1], e2[N << 1];

    void init(int n, int m) {
        idx = cnt1 = cnt2 = 0;
        for (int i = 0; i <= n; i++) h1[i] = h2[i] = -1;
        for (int i = 0; i <= n; i++) belong[i] = low[i] = dfn[i] = 0;
        for (int i = 0; i <= 2*m; i++) bridge[i] = 0;
    }

    void add(int u, int v) {
        e1[cnt1].to = v;
        e1[cnt1].next = h1[u];
        h1[u] = cnt1++;
    }

    void add_cc(int u, int v) {
        e2[cnt2].to = v;
        e2[cnt2].next = h2[u];
        h2[u] = cnt2++;
    }

    void tarjan(int u, int in_edge) {
        dfn[u] = low[u] = ++idx;
        for (int i = h1[u]; ~i; i = e1[i].next) {
            int v = e1[i].to;
            if (!dfn[v]) {
                tarjan(v, i);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) num++, bridge[i] = bridge[i ^ 1] = 1;
            } else if (i != (in_edge ^ 1))
                low[u] = min(low[u], dfn[v]);
        }
    }

    void rebuild(int x) {
        belong[x] = scc;
        for (int i = h1[x]; ~i; i = e1[i].next) {
            int v = e1[i].to;
            if (belong[v] || bridge[i]) continue;
            rebuild(v);
        }
    }
}cc;
void solve() {
	cc.init(n, m);
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        cc.add(u, v), cc.add(v, u);
    }
    for (int i = 1; i <= n; i++) if (!cc.dfn[i]) cc.tarjan(i, 0);
    for (int i = 1; i <= n; i++) {
        if (!cc.belong[i]) {
            ++cc.scc; cc.rebuild(i);
        }
    }
    for (int i = 0; i < cc.cnt1; i+=2) {
        int u = cc.e1[i].to, v = cc.e1[i^1].to;
        if (cc.belong[u] == cc.belong[v]) continue;
        cc.add_cc(cc.belong[u], cc.belong[v]), cc.add_cc(cc.belong[v], cc.belong[u]);
        in[cc.belong[u]]++, in[cc.belong[v]]++;
    }
}