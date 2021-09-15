#include <bits/stdc++.h>
using namespace std;
#define ACM_LOCAL
#define lc u << 1
#define rc u << 1 | 1
const int N = 2e5 + 5;
const int INF = 0x3f3f3f3f;
typedef unsigned long long ull;
typedef pair<int, int> PII;
typedef long long ll;

int n, m, p;
int v[N << 1];
struct node {
    int l, r;
    ll len;
    int cover;
}t[N << 3];

struct L{
    int x;
    int y1, y2;
    int state;
    bool operator < (L &rhs) {
        return x < rhs.x;
    }
}line[N << 1];

void push_up(int u) {
    if (t[u].cover) t[u].len = t[u].r - t[u].l;
    else t[u].len = t[lc].len + t[rc].len;
}

void build(int u, int l, int r) {
    t[u].l = v[l], t[u].r = v[r];
    if (r - l <= 1) return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid, r);
    push_up(u);
}

void update(int u, int ql, int qr, int v) {
    if (ql <= t[u].l && qr >= t[u].r) {
        t[u].cover += v;
        push_up(u);
        return;
    }
    if (ql < t[rc].l) update(lc, ql, qr, v);
    if (qr > t[lc].r) update(rc, ql, qr, v);
    push_up(u);
}

void solve() {
    cin >> n;    
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        v[i] = y1, v[i+n] = y2;
        line[i] = {x1, y1, y2, 1};
        line[i + n] = {x2, y1, y2, -1};
    }
    sort(v+1, v+(n<<1)+1);
    sort(line+1, line+(n<<1)+1);
    build(1, 1, n<<1);
    ll ans = 0;
    for (int i = 1; i <= n<<1; i++) {
        ans += 1ll*t[1].len * (line[i].x - line[i-1].x);
        update(1, line[i].y1, line[i].y2, line[i].state);
    }
    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
    return 0;
}