typedef long long ll;
const int N = 1e5 + 5, M = 5e5 + 5, INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;

int n, q, a[N];

struct Segment_tree {
#define ls u << 1
#define rs u << 1 | 1
    int L[N << 2], R[N << 2];
    ll sum[N << 2], lazy[N << 2];
    
    void push_up(int u) {
        sum[u] = sum[ls] + sum[rs] + (R[u] - L[u] + 1) * lazy[u];
    }

    void build(int u, int l, int r) {
        L[u] = l, R[u] = r;
        if (l == r) {
            sum[u] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(ls, l, m);
        build(rs, m + 1, r);
        push_up(u);
    }

    void update(int u, int ql, int qr, ll k) {
        if (ql <= L[u] && R[u] <= qr) {
            sum[u] += (R[u] - L[u] + 1) * k;
            lazy[u] += k;
            return;
        }
        int m = (L[u] + R[u]) >> 1;
        if (ql <= m) update(ls, ql, qr, k);
        if (qr > m) update(rs, ql, qr, k);
        push_up(u);
    }

    ll query(int u, int ql, int qr, ll tg) {
        if (ql <= L[u] && R[u] <= qr) return sum[u] + (R[u] - L[u] + 1) * tg;
        int m = (L[u] + R[u]) >> 1;
        ll ans = 0;
        if (ql <= m) ans += query(ls, ql, qr, tg + lazy[u]);
        if (qr > m) ans += query(rs, ql, qr, tg + lazy[u]);
        return ans;
    }

#undef ls
#undef rs
} tr;