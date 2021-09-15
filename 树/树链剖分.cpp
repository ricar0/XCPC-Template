const int N = 1e5 + 10;
vector<int> g[N];
int son[N], siz[N], dep[N], fat[N], dfn[N], rnk[N], top[N], tot;
void dfs1(int u, int fa) {
    son[u] = -1; siz[u] = 1; dep[u] = dep[fa] + 1; fat[u] = fa;
    for (auto v : g[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int t) {
    rnk[dfn[u] = ++tot] = u; top[u] = t;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (auto v : g[u]) {
        if (v != son[u] && v != fat[u]) dfs2(v, v);
    }
}