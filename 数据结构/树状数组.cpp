#include <bits/stdc++.h>//区间修改，区间查询
typedef long long ll;
const int N=1e5 + 10;;
ll c1[N],c2[N],n,m,a[N];

inline int lowbit(ll x){ return x & -x;}

void add(ll x,ll k) {
    for(ll i = x; i <= n; i += lowbit(i)) {
        c1[i] += k;
        c2[i] += x*k;
    }
}

ll ask(ll x) {
    ll ans = 0;
    for(ll i = x; i > 0; i -= lowbit(i)) ans += (x+1) * c1[i] - c2[i];
    return ans;
}

void modify(int x, int y, ll k) {
    add(x,k);
    add(y+1,-k);
}

ll query(int x, int y) {
    return ask(y) - ask(x-1);
}

------------------------------------------------------------------------------
template <typename T>
struct BIT {
	const int n;
	vector<T> a;
	BIT(int n) :n(n), a(n){}
	void add(int x, T v) {
		for (int i = x; i <= n; i += i&-i) {
			a[i] += v;
		}
	}
	void rangeAdd(int x, int y, T v) {
		add(x, v);
		add(y+1, -v);
	}
	T sum(int x) {
		T ans = 0;
		for (int i = x; i > 0; i -= i & -i) {
			ans += a[i];
		}
		return ans;
	}
	T rangeSum(int l, int r) {
		return sum(r) - sum(l-1);
	}
};
