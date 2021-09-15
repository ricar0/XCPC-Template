#include <bits/stdc++.h>
#define ACM_LOCAL
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 1e5 + 100, M = 5e5 + 5, INF = 0x3f3f3f3f;
mt19937 rnd(233);
struct Treap {
    int lc[N], rc[N], val[N], key[N], sz[N];
    int cnt, root;

    inline int newnode(int v) {
        val[++cnt] = v;
        key[cnt] = rnd();
        sz[cnt] = 1;
        return cnt;
    }

    inline void update(int now) {
        sz[now] = sz[lc[now]] + sz[rc[now]] + 1;
    }

    void split(int now, int v, int &x, int &y) {
        if (!now) x = y = 0;
        else {
            if (val[now] <= v) {
                x = now;
                split(rc[now], v, rc[now], y);
            } else {
                y = now;
                split(lc[now], v, x, lc[now]);
            }
            update(now);
        }
    }

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (key[x] > key[y]) {
            rc[x] = merge(rc[x], y);
            update(x);
            return x;
        } else {
            lc[y] = merge(x, lc[y]);
            update(y);
            return y;
        }
    }

    int x, y, z;

    inline void insert(int val) {
        split(root, val, x, y);
        root = merge(merge(x, newnode(val)), y);
    }

    inline void del(int val) {
        split(root, val, x, z);
        split(x, val - 1, x, y);
        y = merge(lc[y], rc[y]);
        root = merge(merge(x, y), z);
    }

    inline int getrank(int v) { //查询v的排名
        split(root, v - 1, x, y);
        int rank = sz[x] + 1;
        root = merge(x, y);
        return rank;
    }

    inline int getnum(int rank) {//查询排名第rank的数
        int now = root;
        while (now) {
            if (sz[lc[now]] + 1 == rank)
                break;
            else if (sz[lc[now]] >= rank)
                now = lc[now];
            else {
                rank -= sz[lc[now]] + 1;
                now = rc[now];
            }
        }
        return val[now];
    }

    inline int pre(int v) {
        split(root, v - 1, x, y);
        int now = x;
        while (rc[now])
            now = rc[now];
        int pre = val[now];
        root = merge(x, y);
        return pre;
    }

    inline int nxt(int v) {
        split(root, v, x, y);
        int now = y;
        while (lc[now])
            now = lc[now];
        int nxt = val[now];
        root = merge(x, y);
        return nxt;
    }
}fhq;