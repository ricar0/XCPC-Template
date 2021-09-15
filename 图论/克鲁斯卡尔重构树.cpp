#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int M = 2e5 + 10;
struct Edge {
    int u, v, w;
    bool operator < (const Edge &rhs) const {
        return w > rhs.w;
        // > 最大边中的最小值
        // < 最小边中的最大值
    }
} e[M];
int n, m, son[N], dep[N], pre[N], siz[N], top[N], tot, q, rnk[N], dfn[N], fat[N];
int cnt, val[N], fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

vector<int> g[N];

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

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]])
            u = pre[top[u]];
        else
            v = pre[top[v]];
    }
    return dep[u] > dep[v] ? v : u;
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
        if (!siz[i]) {//未访问过
            int rt = find(i);//下树剖lca
            dfs1(rt, 0); dfs2(rt, rt);
        }
}