#include <bits/stdc++.h>
using namespace std;
const int N = 4e4 + 10;

int h[N], dis[N], d[N], f[N][30];
int T, n, m, cnt, s;

struct edge {
    int to, next, vi;
}e[N<<1];

void add(int u, int v, int vi) {
    e[cnt].to = v;
    e[cnt].vi = vi;
    e[cnt].next = h[u];
    h[u] = cnt++;
}

void dfs(int x, int fa) {
    f[x][0] = fa, d[x] = d[fa] + 1;
    for (int i = 1; i <= 20; i++) f[x][i] = f[f[x][i-1]][i-1];
    for (int i = h[x]; ~i; i = e[i].next) {
        int y = e[i].to;
        if (y != fa) dfs(y, x);
    }
}

int lca(int x, int y) {
    if (d[x] > d[y]) swap(x, y);
    for (int i = 20; i >= 0; i--) if (d[f[y][i]] >= d[x]) y = f[y][i];

    if (x == y) return y;
    for (int i = 20; i >= 0; i--) {
        if (f[y][i] != f[x][i]) {
            y = f[y][i];
            x = f[x][i];
        }
    }
    return f[x][0];
}

int main() {
    memset(h, -1, sizeof h);
    scanf("%d %d %d", &n, &m, &s);
    for (int i = 1; i <= n - 1; i++) {
        int a, b, c;
        scanf("%d %d", &a, &b);
        add(a, b, 1), add(b, a, 1);
    }
    dfs(s, 0);
    for (int i = 1; i <= m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", lca(a, b));
    }
}