#include <bits/stdc++.h>
using namespace std;
#define ACM_LOCAL
const int N = 2e6 + 10;
int n, m, k, a[N], cnt[N], qnum, cnum, pos[N];
int Ans, ans[N], x, y;
char op;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}

struct node {
    int l, r, pre, id;
}q[N];

struct node2 {
    int val, pos;
}c[N];

bool cmp(node x, node y) {
    if (x.l != y.l) return pos[x.l] < pos[y.l];
    if (x.r != y.r) return pos[x.r] < pos[y.r];
    return x.pre < y.pre;
}

inline void add(int x) {if (++cnt[a[x]] == 1) ++Ans;}

inline void sub(int x) {if (--cnt[a[x]] == 0) --Ans;}
    

inline void work(int now, int i) {
    if (c[now].pos >= q[i].l && c[now].pos <= q[i].r) {
        if (--cnt[a[c[now].pos]] == 0) --Ans;
        if (++cnt[c[now].val] == 1) ++Ans;
    }
    swap(c[now].val, a[c[now].pos]);// 浜ゆ崲鏀瑰彉鐨勫€煎拰鍘熸潵鐨勫€硷紝鏂逛究鍥為€€鐨勬椂鍊欏鍘?
}

void solve() {
    n = read(), m = read();
    int siz = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; ++i) a[i] = read(), pos[i] = (i - 1) / siz + 1;
    
    while (m--) {
        op = getchar();
        if (op == 'Q') {
            q[++qnum].l = read();
            q[qnum].r = read();
            q[qnum].id = qnum;
            q[qnum].pre = cnum; 
        }
        else {
            c[++cnum].pos = read();
            c[cnum].val = read();
        }
    }
    
    sort(q+1, q+qnum+1, cmp);
    int l = 1, r = 0, now = 0;
    for (int i = 1; i <= qnum; ++i) {
        while (q[i].l < l) add(--l);
        while (q[i].r > r) add(++r);
        while (q[i].l > l) sub(l++);
        while (q[i].r < r) sub(r--);
        while (now < q[i].pre) work(++now, i);
        while (now > q[i].pre) work(now--, i);
        ans[q[i].id] = Ans;
    }

    for (int i = 1; i <= qnum; ++i)  printf("%d\n", ans[i]);
}

signed main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
//#else
    solve();
#endif
    return 0;
}