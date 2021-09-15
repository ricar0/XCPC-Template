#include <bits/stdc++.h>
using namespace std;
#define ACM_LOCAL
const int N = 1e5 + 10;
int n, m, k, a[N], pos[N], b[N], upa[N], prea[N], sum[N], Ans, ans[N];

inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}

struct Q{
    int l, r, id;
}p[N];

bool cmp(Q x, Q y) {
    if (pos[x.l] == pos[y.l]) return x.r < y.r;
    else return pos[x.l] < pos[y.l];
}

inline int lowbit(int x) {return x & -x;}

void add(int p, int v) {for (int i = p; i <= 3*n+10; i += lowbit(i)) sum[i] += v;}

int query(int p) {
    int res = 0;
    for (int i = p; i > 0; i -= lowbit(i)) res += sum[i];
    return res;
}
int query_(int l, int r) {return query(r) - query(l-1);}

void solve() {
    n = read(), m = read(), k = read();
    int tot = 0;
    int siz = sqrt(n);
    for (int i = 1; i <= n; i++) a[i] = read();

    for (int i = 1; i <= n; i++) {
        upa[i] = a[i] + k, prea[i] = a[i] - k;
        b[++tot] = a[i], b[++tot] = upa[i], b[++tot] = prea[i];
    }
    sort(b + 1, b + tot + 1);
    int cnt = unique(b + 1, b + tot + 1) - b - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b+1, b+cnt+1, a[i]) - b;
        upa[i] = lower_bound(b+1, b+cnt+1, upa[i]) - b;
        prea[i] = lower_bound(b+1, b+cnt+1, prea[i]) - b;
    }

    for (int i = 1; i <= m; i++) {
        p[i].l = read(), p[i].r = read();
        p[i].id = i;
    }
    sort(p + 1, p + m + 1, cmp);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++) {
        while (p[i].l < l) {
            l--;
            Ans += query_(prea[l], upa[l]);
            add(a[l], 1);
        }
        while (p[i].l > l) {
            add(a[l], -1);
            Ans -= query_(prea[l], upa[l]);
            l++;
        }
        while (p[i].r < r) {
            add(a[r], -1);
            Ans -= query_(prea[r], upa[r]);
            r--;
        }
        while (p[i].r > r) {
            r++;
            Ans += query_(prea[r], upa[r]);
            add(a[r], 1);
        }
        ans[p[i].id] = Ans;
    }
    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
//#else
    solve();
#endif
    return 0;
}