#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <string>
#include <set>
#include <map>
#include <bitset>
using namespace std;
#define ACM_LOCAL

const int INF = 0x3f3f3f3f;
const int N = 2e5 + 5;
typedef pair<int, int> PII;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

struct node {
	int l, r;
	int val;
}t[N * 40 * 2];

int cnt, tot, rootdep[N], rootfa[N], n, m;

void build(int l, int r, int &now) {
	now = ++cnt;
	if (l == r) {
        t[now].val = ++tot;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, t[now].l);
    build(mid + 1, r, t[now].r);
}

void update(int l, int r, int ver, int &now, int pos, int val) {
    t[now = ++cnt] = t[ver];
    if (l == r) {
        t[now].val = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(l, mid, t[ver].l, t[now].l, pos, val);
    else update(mid + 1, r, t[ver].r, t[now].r, pos, val);
}

int query(int l, int r, int &now, int pos) {
    if (l == r) return t[now].val;
    int mid = (l + r) >> 1;
    if (pos <= mid) return query(l, mid, t[now].l, pos);
    else return query(mid + 1, r, t[now].r, pos);
}

int find(int ver, int x) {
    int fx = query(1, n, rootfa[ver], x);
    return fx == x ? x : find(ver, fx);
} 

void merge(int ver, int x, int y) {
    x = find(ver-1, x);
    y = find(ver-1, y);
    if (x == y) {
        rootfa[ver] = rootfa[ver-1];
        rootdep[ver] = rootdep[ver-1];
    }
    else {
        int depx = query(1, n, rootdep[ver-1], x);
        int depy = query(1, n, rootdep[ver-1], y);
        if (depx < depy) {
            update(1, n, rootfa[ver-1], rootfa[ver], x, y);
            rootdep[ver] = rootdep[ver-1];
        }
        else if (depx > depy) {
            update(1, n, rootfa[ver-1], rootfa[ver], y, x);
            rootdep[ver] = rootdep[ver-1];
        }
        else {
            update(1, n, rootfa[ver-1], rootfa[ver], x, y);
            update(1, n, rootdep[ver-1], rootdep[ver], y, depy+1);
        }
    }
}