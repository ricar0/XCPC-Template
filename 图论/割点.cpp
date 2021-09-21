#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int dfn[N], low[N], idx, cut[N], siz[N], n, m;
vector<int> g[N];
int n, m;
void tarjan(int u, int root) {
    dfn[u] = low[u] = ++idx;
    int child = 0;
    for (auto v : g[u]) {
        if (!dfn[v]) {
            tarjan(v, root);
            siz[u] += siz[v];
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                child++;
                if (child > 1 || u != root) cut[u] = 1;
            }
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}
