#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N];

int f[N][30], dep[N];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1; f[u][0] = fa;
    for (int i = 1; i <= 19; i++) f[u][i] = f[f[u][i-1]][i-1];
    for (auto &v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}

int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int i = 19; i >= 0; i--) if (dep[y] - dep[x] >= (1 << i)) y = f[y][i];

    if (x == y) return x;
    for (int i = 19; i >= 0; i--) {
        if (f[y][i] != f[x][i])
            y = f[y][i], x = f[x][i];
    }
    return f[x][0];
}