#include<bits/stdc++.h>
#define lc (son[p][0])
#define rc (son[p][1])
using namespace std;
//#define ACM_LOCAL
const int N = 4e5 + 10;
struct SGT {
    const double alpha = 0.75;
    int st[N], top, tot, rt, son[N][2], fa[N], val[N], siz[N], all[N];
    bool in[N];

    inline int get() { return top ? st[top--] : ++tot; }

    void del(int t) { st[++top] = t; }

    inline void pushup(int p) { siz[p] = siz[lc] + siz[rc] + in[p], all[p] = all[lc] + all[rc] + 1; }

    inline bool check(int p) { return (all[lc] >= all[p] * alpha) || (all[rc] >= all[p] * alpha); }

    inline int newnode(int v = 0, int pa = 0) {
        int p = get();
        lc = rc = 0, val[p] = v, siz[p] = all[p] = 1, in[p] = 1, fa[p] = pa;
        return p;
    }

    inline void getpos(int p, vector<int> &v) {
        if (!p)return;
        getpos(lc, v);
        if (in[p])v.push_back(p);
        else del(p);
        getpos(rc, v);
    }

    inline int build(int l, int r, vector<int> v) {
        if (l >= r)return 0;
        int mid = l + r >> 1, p = v[mid];
        lc = build(l, mid, v), rc = build(mid + 1, r, v), fa[lc] = fa[rc] = p;
        return pushup(p), p;
    }

    inline void rebuild(int &p) {
        static vector<int> v;
        v.clear();
        int pa = fa[p];
        getpos(p, v);
        fa[(p = build(0, v.size(), v))] = pa;
    }

    inline int rank(int v) {
        int p = rt, ret = 1;
        while (p) {
            if (v <= val[p])p = lc;
            else ret += siz[lc] + in[p], p = rc;
        }
        return ret;
    }

    inline int kth(int k) {
        int p = rt;
        while (p) {
            if (siz[lc] + 1 == k && in[p]) break;
            if (siz[lc] >= k)p = lc;
            else k -= siz[lc] + in[p], p = rc;
        }
        return val[p];
    }

    inline int insert(int &p, int v) {
        if (!p)return p = newnode(v), 0;
        ++siz[p], ++all[p];
        int ret;
        ret = insert(v <= val[p] ? lc : rc, v), pushup(p);
        if (check(p))ret = p;
        return ret;
    }

    inline void insert(int v) {
        int p = insert(rt, v);
        if (!p)return;
        if (p == rt)rebuild(rt);
        else {
            int f = fa[p];
            if (p == son[f][0])rebuild(son[f][0]);
            else rebuild(son[f][1]);
        }
    }

     void erase(int p, int k) {
        --siz[p];
        if (in[p] && k == siz[lc] + in[p]) {
            in[p] = 0;
            return;
        }
        if (k <= siz[lc])erase(lc, k);
        else erase(rc, k - siz[lc] - in[p]);
    }

     void erase(int v) {
        erase(rt, rank(v));
        if (siz[rt] < alpha * all[rt])rebuild(rt);
    }

     int pre(int v) { return kth(rank(v) - 1); }

     int suf(int v) { return kth(rank(v + 1)); }
} tzy;

