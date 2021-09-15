
//bfs版
#include <bits/stdc++.h>
using namespace std;
double eps = 1e-4;
const int N = 1e3 + 5;
const int M = 5e3 + 5;
struct edge {
    int to, next;
    double vi;
}e[M * 2];

int vis[N], n, cnt, m, h[N], times[N];
double dis[N];
int ve[N];

void add(int u, int v, double w) {
    e[cnt].to = v;
    e[cnt].vi = w;
    e[cnt].next = h[u];
    h[u] = cnt++;
}
bool spfa(double mid) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
        vis[i] = 1, dis[i] = 0, times[i] = 0;
    }
    while (q.size()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (int i = h[u]; ~i; i = e[i].next) {
            int v = e[i].to;
            double va = mid * e[i].vi - (double)ve[u];
            if (dis[v] > dis[u] + va) {
                dis[v] = dis[u] + va;
                times[v] = times[u] + 1;
                if (times[v] >= n) return true;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
    return false;
}

//dfs版
#include <bits/stdc++.h>
using namespace std;
double eps = 1e-9;
const int N = 3e3 + 5;
const int M = 1e4 + 5;
struct edge {
    int to, next;
    double vi;
}e[M << 1];

int vis[N], n, cnt, m, h[N], times[N], flag;
double dis[N];

void add(int u, int v, double w) {
    e[cnt].to = v;
    e[cnt].vi = w;
    e[cnt].next = h[u];
    h[u] = cnt++;
}
void spfa(int u, double mid) {
    vis[u] = 1;
    for (int i = h[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        double tmp = dis[u] + e[i].vi - mid;
        if (dis[v] > tmp) {
            dis[v] = tmp;
            if (vis[v]) {
                flag = 1;
                return;
            }
            spfa(v, mid);
        }
    }
    vis[u] = 0;
}

bool check(double mid) {
    memset(vis, 0, sizeof vis);
    memset(times, 0, sizeof times);
    for (int i = 1; i <= n; i++) dis[i] = 0;
    for (int i = 1; i <= n; i++) {
        flag = 0;
        spfa(i, mid);
        if (flag) return true;
    }
    return false;
}

int main() {
    scanf("%d %d", &n, &m);
    memset(h, -1, sizeof h);

    for (int i = 1; i <= m; i++) {
        int x, y;
        double z;
        scanf("%d %d %lf", &x, &y, &z);
        add(x, y, z);
    }

    double l = -1e5, r = 1e5, mid;
    while (r - l > eps) {
        mid = (l + r) * 0.5;
        if (check(mid)) r = mid;
        else l = mid;
    }
    printf("%.8lf", mid);
}