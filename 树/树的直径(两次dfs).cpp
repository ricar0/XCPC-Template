#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int dis[N], n, m, p, q, vis[N], pre[N];
vector<int> g[N];

int dfs(int u, int fa) {
    int maxpos = u;
    for (auto v : g[u]) {
        if (vis[v] || v == fa) continue;
        dis[v] = dis[u] + 1;
        pre[v] = u;
        int z = dfs(v, u);
        if (dis[z] > dis[maxpos]) maxpos = z;
    }
    return maxpos;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    p = dfs(1, 0);
    dis[p] = 0;
    q = dfs(p, 0);

    cout << dis[q] << endl;
}
/*
7 6
1 2
1 3
2 4
2 5
3 6
3 7
*/
