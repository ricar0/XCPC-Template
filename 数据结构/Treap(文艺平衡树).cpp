#include <bits/stdc++.h>
#define ACM_LOCAL
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 1e5 + 10, M = 1e5 + 10, INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
mt19937 rnd(233);
struct Treap {
    int key[N], lc[N], rc[N], val[N], sz[N];
    bool reverse[N];
    ll sum[N], tag[N];
    int cnt, rt;

    inline int newnode(int v) {
        val[++cnt] = v;
        sz[cnt] = 1;
        key[cnt] = rnd();
        reverse[cnt] = false;
        return cnt;
    }
    inline void push_up(int now) {
        sz[now] = sz[lc[now]] + sz[rc[now]] + 1;
        sum[now] = sum[lc[now]] + sum[rc[now]] + val[now];
    }
    inline void push_down(int now) {
        if (reverse[now]) {
            swap(lc[now], rc[now]);
            reverse[lc[now]] ^= 1;
            reverse[rc[now]] ^= 1;
            reverse[now] = false;
        }
        if (tag[now]) {
            sum[lc[now]] += sz[lc[now]] * tag[now];
            val[lc[now]] += tag[now];
            tag[lc[now]] += tag[now];

            sum[rc[now]] += sz[rc[now]] * tag[now];
            val[rc[now]] += tag[now];
            tag[rc[now]] += tag[now];
        }
        tag[now] = 0;
    }
    void split(int now, int siz, int &x, int &y) {
        if (!now) x = y = 0;
        else {
            push_down(now);
            if (sz[lc[now]] < siz) {
                x = now;
                split(rc[now], siz-sz[lc[now]]-1, rc[now], y);
            } else {
                y = now;
                split(lc[now], siz, x, lc[now]);
            }
            push_up(now);
        }
    }
    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (key[x] < key[y]) {
            push_down(x);
            rc[x] = merge(rc[x], y);
            push_up(x);
            return x;
        } else {
            push_down(y);
            lc[y] = merge(x, lc[y]);
            push_up(y);
            return y;
        }
    }
    void rev(int l, int r) {
        int x, y, z;
        split(rt, l-1, x, y);
        split(y, r-l+1, y, z);
        reverse[y] ^= 1;
        rt = merge(merge(x, y), z);
    }
    void ldr(int now) {
        if (!now) return;
        push_down(now);
        ldr(lc[now]);
        printf("%d ", val[now]);
        ldr(rc[now]);
    }
    void add(int l, int r, int v) {
        int x, y, z;
        split(rt, l-1, x, y);
        split(y, r-l+1, y, z);
        tag[y] += v;
        sum[y] += sz[y] * v;
        val[y] += v;
        rt = merge(merge(x, y), z);
    }
    ll query(int l, int r) {
        ll ans = 0;
        int x, y, z;
        split(rt, l-1, x, y);
        split(y, r-l+1, y, z);
        ans = sum[y];
        rt = merge(merge(x, y), z);
        return ans;
    }
    void insert(int pos, int v) {
        int x, y, z;
        split(rt, pos-1, x, y);
        z = newnode(v);
        rt = merge(merge(x, z), y);
    }
}fhq;