#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;

int a[N], b[N], rt[N];
int n, m;
struct Hash {
    int b[N], tot;
    void init() {tot = 0;}
    void insert(int x) {b[++tot] = x;}
    void build() {
        sort(b+1, b+1+tot);
        tot = unique(b+1, b+tot+1) - (b+1);
    }
    int pos(int x) {return lower_bound(b+1, b+tot+1, x) - b;}
}ha;
struct {
    int t[N << 5], lc[N << 5], rc[N << 5];
    int NodeNum = 0;
    ll sum[N << 5];
    int build(int l, int r) {
        int num = ++NodeNum;
        if (l != r) {
            int mid = (l + r) >> 1;
            lc[num] = build(l, mid);
            rc[num] = build(mid + 1, r);
        }
        return num;
    }
    int update(int pre, int l, int r, int x) {
        int num = ++NodeNum;
        lc[num] = lc[pre], rc[num] = rc[pre], t[num] = t[pre] + 1;
        if (l != r) {
            int mid = (l + r) >> 1;
            if (x <= mid) lc[num] = update(lc[pre], l, mid, x);
            else rc[num] = update(rc[pre], mid + 1, r, x);
        }
        return num;
    }
    int Qry_Kth_Num(int u, int v, int l, int r, int k) {
        if (l == r) return ha.b[l];
        int mid = (l + r) >> 1, num = t[lc[v]] - t[lc[u]];
        if (num >= k) return Qry_Kth_Num(lc[u], lc[v], l, mid, k);
        else return Qry_Kth_Num(rc[u], rc[v], mid + 1, r, k-num);
    }
    ll Qry_Kth_Sum(int u, int v, int l, int r, int k) {//k大数之和
        if (l == r) return 1ll*ha.b[l] * k;
        int mid = (l + r) >> 1, num = t[rc[v]] - t[rc[u]];
        if (num >= k) return Qry_Kth_Sum(rc[u], rc[v], mid+1, r, k);
        else return sum[rc[v]] - sum[rc[u]] + Qry_Kth_Sum(lc[u], lc[v], l, mid, k-num);
    }
    int Binary_Search(int left, int right, int val) {//查找小于等于val的个数
        int l = 1, r = right - left + 1;
        while (l <= r) {
            int mid = l + r >> 1;
            int num = Qry_Kth_Num(rt[left - 1], rt[right], 1, ha.tot, mid);
            if (num > val) r = mid - 1;
            else l = mid + 1;
        }
        return r;
    }
}hjt;