#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
typedef long long ll;
typedef pair<int, int> PII;

struct Edge {
    int to, next, w;
}e[N<<1];

int h[N], cnt;
void add(int u, int v, int w) {
    e[cnt].to = v;
    e[cnt].w = w;
    e[cnt].next = h[u];
    h[u] = cnt++;
}
int n, m, k;
struct Node {
    vector<PII> g[N];
    int vis[N];
    ll dis[N];
    void init() {
        for (int i = 1; i <= n; i++) g[i].clear();
    }

    struct node {
        int now; ll d;
        bool operator < (const node &rhs) const {
            return d > rhs.d;
        }
    };

    void dij(int st) {
        memset(dis, 0x3f, sizeof dis);
        memset(vis, 0, sizeof vis);
        dis[st] = 0; priority_queue<node> q;
        q.push({st, dis[st]});
        while (q.size()) {
            int u = q.top().now;
            q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto item : g[u]) {
                int v = item.first;
                int w = item.second;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    if (!vis[v]) {
                        q.push({v, dis[v]});
                    }
                }
            }
        }
    }
}Dij;
int tap[N];
void build_tree(int x) {
    tap[x] = 1;
    for (auto item : Dij.g[x]) {
        int v = item.first;
        int w = item.second;
        if (tap[v]) continue;
        if (Dij.dis[v] == Dij.dis[x] + w) {
            add(x, v, w), add(v, x, w);
            build_tree(v);
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    Dij.init();
    for (int i = 1; i <= m; i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        Dij.g[u].push_back(PII{v, w});
        Dij.g[v].push_back(PII{u, w});
    }
    Dij.dij(1);
    for (int i = 1; i <= n; i++)
        sort(Dij.g[i].begin(), Dij.g[i].end());
    memset(h, -1, sizeof h);
    build_tree(1);
}