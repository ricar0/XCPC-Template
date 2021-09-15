#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#include <cmath>
#include <bitset>
#include <map>

using namespace std;
typedef long long ll;
const int N = 1e4 + 5, M = 2e5 + 5, INF = 0x3f3f3f3f;

struct Edge {
    int to, next, vi;
} e[N << 1];

int h[N], cnt;

void add(int u, int v, int w) {
    e[cnt].to = v;
    e[cnt].vi = w;
    e[cnt].next = h[u];
    h[u] = cnt++;
}

ll ans = 0;
int root, sum, n;
int sz[N], mx[N], vis[N];

void getroot(int x, int fa) {
    sz[x] = 1, mx[x] = 0;
    for (int i = h[x]; ~i; i = e[i].next) {
        int y = e[i].to;
        if (vis[y] || y == fa) continue;
        getroot(y, x);
        sz[x] += sz[y];
        mx[x] = max(mx[x], sz[y]);
    }
    mx[x] = max(mx[x], sum - sz[x]);
    if (mx[x] < mx[root]) root = x;
}

int d[N], dep[N];

void getd(int x, int fa) {
    d[++d[0]] = dep[x];
    for (int i = h[x]; ~i; i = e[i].next) {
        int y = e[i].to;
        if (vis[y] || y == fa) continue;
        dep[y] = dep[x] + e[i].vi;
        getd(y, x);
    }
}

int K;

int cal(int x, int now) {
    dep[x] = now, d[0] = 0;
    getd(x, -1);
    sort(d + 1, d + d[0] + 1);
    int res = 0, l = 1, r = d[0];
    while (l < r) {
        if (d[l] + d[r] > K) r--;
        else res += r - l, l++;
    }
    return res;
}

void work(int x) {
    ans += cal(x, 0);
    vis[x] = 1;
    for (int i = h[x]; ~i; i = e[i].next) {
        int y = e[i].to;
        if (vis[y]) continue;
        ans -= cal(y, e[i].vi);
        sum = sz[y], root = 0;
        getroot(y, -1);
        work(root);
    }
}

int main() {
    while (scanf("%d %d", &n, &K), n) {
        cnt = 0;
        memset(h, -1, sizeof h);
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n - 1; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w), add(v, u, w);
        }
        root = 0, ans = 0, sum = n, mx[0] = INF;
        getroot(1, -1);
        work(root);
        printf("%lld\n", ans);
    }
}
