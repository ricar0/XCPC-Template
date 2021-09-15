#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int dis[N], n, m, f[N];
int ans;
vector<int> g[N];
void dp(int u, int fa) {
    for (auto v : g[u]) {
        if (v == fa) continue;
        dp(v, u);
        ans = max(ans, f[u] + f[v] + 1);
        f[u] = max(f[u], f[v] + 1);
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i ++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dp(1, 0);

    cout << ans << endl;
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
