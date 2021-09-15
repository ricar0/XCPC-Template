#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
const int M = 5e5 + 10;
typedef long long ll;
struct Node {
    struct Edge {
        int to, next, w;
    }e[M<<1];

    int h[N], cnt, vis[N], count[N];
    ll dis[N];
    void init() {
        memset(h, -1, sizeof h);
        cnt = 0;
    }
    void add(int u, int v, int w) {
        e[cnt].to = v;
        e[cnt].w = w;
        e[cnt].next = h[u];
        h[u] = cnt++;
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
            for (int i = h[u]; ~i; i = e[i].next) {
                int v = e[i].to;
                if (dis[v] > dis[u] + e[i].w) {
                    dis[v] = dis[u] + e[i].w;
                    if (!vis[v]) {
                        q.push({v, dis[v]});
                    }
                }
                else if (dis[v] == dis[u] + e[i].w) {
                    count[v]++;
                }
            }
        }
    }
}Dij;