#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int MAX = 2e5 + 10;
#define ls 2 * u
#define rs 2 * u + 1
int a[MAX];

struct SegmentTree {
	int l, r;
	ll num, add ,mu = 1;
}t[4*MAX];
int n, q;
char c;
int Max;
ll k, mod;
void push_up(int u) {
	t[u].num = (t[ls].num + t[rs].num) % mod;
}

void push_down(int u) {
	t[ls].num = (t[ls].num * t[u].mu) % mod;
	t[rs].num = (t[rs].num * t[u].mu) % mod;
	t[ls].num = (t[ls].num + (t[ls].r - t[ls].l + 1) * t[u].add) % mod;
	t[rs].num = (t[rs].num + (t[rs].r - t[rs].l + 1) * t[u].add) % mod;

	t[ls].mu = (t[ls].mu * t[u].mu) % mod;
	t[rs].mu = (t[rs].mu * t[u].mu) % mod;
	t[ls].add = (t[ls].add * t[u].mu + t[u].add) % mod;
	t[rs].add = (t[rs].add * t[u].mu + t[u].add) % mod;

	t[u].add = 0;
	t[u].mu = 1;
}

void build(int u, int l, int r) {
	t[u].l = l; t[u].r = r;
	t[u].mu = 1;
	if (l == r) {
		t[u].num = a[l] % mod;
		return;
	}
	int m = (l + r) / 2;
	build(ls, l, m);
	build(rs, m + 1, r);
	push_up(u);
}

void add(int u, ll v, int ql, int qr) {
	if (t[u].l >= ql && t[u].r <= qr) {
		t[u].num = (t[u].num + (t[u].r - t[u].l + 1) * v) % mod;
		t[u].add = (t[u].add + v) % mod;
		return;
	}
	push_down(u);
	int mid = (t[u].l + t[u].r) / 2;
	if (ql <= mid) add(ls, v, ql, qr);
	if (qr > mid) add(rs, v, ql, qr);
	push_up(u);
}

void mu(int u, ll v, int ql,int qr) {
	if (t[u].l >= ql && t[u].r <= qr) {
		t[u].num = t[u].num * v % mod;
		t[u].add = t[u].add * v % mod;
		t[u].mu = t[u].mu * v % mod;
		return;
	}
	push_down(u);
	int mid = (t[u].l + t[u].r) / 2;
	if (ql <= mid) mu(ls, v, ql, qr);
	if (qr > mid) mu(rs, v, ql, qr);
	push_up(u);
}

ll query(int u, int ql, int qr) {
	if (t[u].l >= ql && t[u].r <= qr) {
		return t[u].num % mod;
	}
	int res = 0;
	push_down(u);
	int m = (t[u].l + t[u].r) / 2;
	if (ql <= m) res = (res + query(ls, ql, qr)) % mod;
	if (qr > m) res = (res + query(rs, ql, qr)) % mod;
	push_up(u);
	return res;
}
