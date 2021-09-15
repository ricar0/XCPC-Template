#include <bits/stdc++.h>
using namespace std;
#define ACM_LOCAL
const int N = 1e6 + 5;
typedef pair<int, int> PII;
typedef long long ll;

inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int NodeNum, n, m, a[N], rt[N];

struct Node{
	int t[N << 5], lc[N << 5], rc[N << 5];
	
	void build(int l, int r, int &now) {
		now = ++NodeNum;
		if (l == r) t[now] = a[l];
		else {
			int mid = (l + r) >> 1;
			build(l, mid, lc[now]);
			build(mid + 1, r, rc[now]);
		}
	}
	void update(int pre, int l, int r, int &now, int pos, int val) {
		now = ++NodeNum;
		lc[now] = lc[pre], rc[now] = rc[pre], t[now] = t[pre];
		if (l == r) t[now] = val;
		else {
			int mid = (l + r) >> 1;
			if (mid >= pos) update(lc[pre], l, mid, lc[now], pos, val);
			else update(rc[pre], mid + 1, r, rc[now], pos, val);
		}
	}
	void query(int pre, int l, int r, int &now, int pos) {
        now = ++NodeNum;
		lc[now] = lc[pre], rc[now] = rc[pre], t[now] = t[pre];
		if (l == r) printf("%d\n", t[now]);
		else {
			int mid = (l + r) >> 1;
			if (mid >= pos) query(lc[pre], l, mid, lc[now], pos);
			else query(rc[pre], mid + 1, r, rc[now], pos);
		}
	}
}T;


void solve() {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) a[i] = read();

    T.build(1, n, rt[0]);
    for (int i = 1; i <= m; i++) {
        int opt, id, x, y;
        id = read(), opt = read();
        if (opt == 1) {
            x = read(), y = read();
            T.update(rt[id], 1, n, rt[i], x, y);
        }
        else {
            x = read();
            T.query(rt[id], 1, n, rt[i], x);
        }
    }

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