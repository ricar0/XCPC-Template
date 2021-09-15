#include <bits/stdc++.h>
using namespace std;
const int N = 10010;
int h[N], cnt, n, m, scc;
int dfn[N], low[N], idx, tp, in_stk[N], vis[N], sd[N];
set<int> sc[N];
struct edge{
    int to, next;
}e[N*2];

void add(int u, int v) {
    e[cnt].to = v;
    e[cnt].next = h[u];
    h[u] = cnt++;
}

void tarjan(int x) {
    low[x] = dfn[x] = ++idx;
    vis[x] = 1;
    in_stk[++tp] = x;
    for (int i = h[x]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else if (vis[v]) {
            low[x] = min(low[x], dfn[v]);
        }
    }
    if (low[x] == dfn[x]) {
        int y;
        ++scc;
        while(y = in_stk[tp--]) {
            sd[y] = scc;
            vis[y] = 0;
            sc[scc].insert(y);
            if (x == y) break;
        }
    }
}

int main() {
    cin >> n >> m;
    memset(h, -1, sizeof h);
    for (int i = 0; i < m; i ++ ) {
        int x, y;
        cin >> x >> y;
        add(x, y);
    }
    for (int i = 1; i <= n; i ++) if (!dfn[i]) tarjan(i);

    for (int i = 1; i <= scc; i ++) {
        cout << "#" << i << ":";
        for (auto x : sc[i]) {
            cout << x << " ";
        }
        cout << endl;
    }
}