#include <bits/stdc++.h>
using namespace std;
//#define ACM_LOCAL
typedef long long ll;
const int N = 2e5 + 10;
int n, m, k, a[N], pos[N], xl[N], xr[N], b[N], _cnt[N], st[N], ed[N], clear[N];
int Max, temp, ans[N], num;

inline int read(){
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}

struct node {
    int l, r, id;
    bool operator < (node xx) const {
        if(pos[l] == pos[xx.l]) return r < xx.r;
        else return pos[l] < pos[xx.l];
    }
}q[N];

void solve() {
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read(), b[i] = a[i];

    sort(b+1, b+n+1);
    int tot = unique(b+1, b+n+1) - b-1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b+1, b+tot+1, a[i]) - b;

    m = read();
    for (int i = 1; i <= m; i++) q[i].l = read(), q[i].r = read(), q[i].id = i;

    int siz = sqrt(n);
    for (int i = 1; i <= n; i++){
        pos[i] = i / siz;
        xl[pos[i]] = (xl[pos[i]] == 0 || xl[pos[i]] > i) ? i : xl[pos[i]];
        xr[pos[i]] = (xr[pos[i]] < i) ? i : xr[pos[i]];
    }

    sort(q+1, q+m+1);

    int l = 1, r = 0, lastblock = -1;
    
    for (int i = 1; i <= m; i++) {
        if (pos[q[i].l] == pos[q[i].r]) {
            int temp = 0;
            for (int j = q[i].l; j <= q[i].r; j++) {
                if (!_cnt[a[j]]) _cnt[a[j]] = j;
                else temp = max(temp, j - _cnt[a[j]]);
            }
            for (int j = q[i].l; j <= q[i].r; j++) _cnt[a[j]] = 0;
            ans[q[i].id] = temp;
        }
        else {
            if (lastblock != pos[q[i].l]) {
                l = xr[pos[q[i].l]] + 1;
                r = l - 1;
                for (int j = 1; j <= num; j++) st[clear[j]] = ed[clear[j]] = 0;
                num = 0;
                Max = 0, lastblock = pos[q[i].l];
            }
            while (r < q[i].r) {
                r++;
                ed[a[r]] = r;
                clear[++num] = a[r];
                if (!st[a[r]]) st[a[r]] = r;
                Max = max(Max, r - st[a[r]]);
            }
            temp = Max;
            while (l > q[i].l) {
                l--;
                if (ed[a[l]]) temp = max(temp, ed[a[l]] - l);
                else ed[a[l]] = l;
            }
            while (l < xr[pos[q[i].l]] + 1) {
                if (ed[a[l]] == l) ed[a[l]] = st[a[l]] = 0;
                l++;
            }
            ans[q[i].id] = temp;
        }
    }

    for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}

signed main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
    return 0;
}