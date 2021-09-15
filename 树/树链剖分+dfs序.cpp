#pragma GCC optimize (2)
#include <bits/stdc++.h>
//#define ACM_LOCAL
using namespace std;
#define lc u << 1
#define rc u << 1 | 1
const int N = 60010;
const int inf = 2e9;
int n, a, b, w[N], q, tot, m;
int cnt, h[N];
int siz[N], top[N], son[N], dep[N], fa[N], dfn[N], rnk[N];
char op[10];
struct edge {
    int to, next;
}e[N << 1];

inline void add(int u, int v) {
    e[cnt].to = v;
    e[cnt].next = h[u];
    h[u] = cnt++;
}

struct SegTree {
    int sum[N << 2], maxx[N << 2], L[N << 2], R[N << 2], tag[N << 2];
    void push_up(int u) {
        sum[u] = sum[lc] + sum[rc];
        maxx[u] = max(maxx[lc], maxx[rc]);
    }
    void push_down(int u) {
        if (tag[u]) {
            tag[lc] += tag[u];
            tag[rc] += tag[u];
            sum[lc] += (R[lc] - L[lc] + 1) * tag[u];
            sum[rc] += (R[rc] - L[rc] + 1) * tag[u];
            maxx[lc] += tag[u];
            maxx[rc] += tag[u];
            tag[u] = 0;
        }
    }

    void build(int u, int l, int r) {
        L[u] = l, R[u] = r;
        maxx[u] = -inf, sum[u] = 0;
        if (l == r) {
            sum[u] = maxx[u] = w[rnk[l]];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        push_up(u);
    }
    int query1(int u, int ql, int qr) {
        if (ql <= L[u] && R[u] <= qr) return maxx[u];
        int mid = (L[u] + R[u]) >> 1;
        push_down(u);
        int res = -inf;
        if (ql <= mid) res = max(res, query1(lc, ql, qr));
        if (qr > mid) res = max(res, query1(rc, ql, qr));
        return res;
    }
    int query2(int u, int ql, int qr) {
        if (ql <= L[u] && R[u] <= qr) return sum[u];
        int mid = (L[u] + R[u]) >> 1;
        push_down(u);
        int res = 0;
        if (ql <= mid) res += query2(lc, ql, qr);
        if (qr > mid) res += query2(rc, ql, qr);
        return res;
    }
    void update(int u, int ql, int qr, int v) {
        if (L[u] >= ql && qr >= R[u]) {
            sum[u] += (R[u] - L[u] + 1) * v;
            tag[u] += v;
            maxx[u] += v;
            return;
        }
        push_down(u);
        int mid = (L[u] + R[u]) >> 1;
        if (ql <= mid) update(lc, ql, qr, v);
        if (qr > mid) update(rc, ql, qr, v);
        push_up(u);
    }
} st;

void dfs1(int u) {
    son[u] = -1;
    siz[u] = 1;
    for (int i = h[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (!siz[v]) {
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v);
            siz[u] += siz[v];
            if (son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
        }
    }
}

void dfs2(int u, int t) {
    top[u] = t;
    dfn[u] = ++tot;
    rnk[tot] = u;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (int i = h[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v != son[u] && v != fa[u]) dfs2(v, v);
    }
}
int querymax(int x, int y) {
    int ans = -1;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = max(ans, st.query1(1, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y]) swap(x, y);
    ans = max(ans, st.query1(1, dfn[x], dfn[y]));//在点权转化成边权时，dfn[x]+1开始
    return ans;
}

int querysum(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ans += st.query2(1, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y]) swap(x, y);
    ans += st.query2(1, dfn[x], dfn[y]);
    return ans;
}

void update(int x, int y, int c) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        st.update(1, dfn[top[x]], dfn[x], c);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y]) swap(x, y);
    st.update(1, dfn[x], dfn[y], c);
}