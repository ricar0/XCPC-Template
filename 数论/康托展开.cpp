#include <bits/stdc++.h>//康拓展开
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
const int Mod = 998244353;
int T, n;
ll a[N], fac[N], c[N];
inline int lowbit(int x) { return x & -x; }
void add(int x, int v) {
	for (int i = x; i <= n; i += lowbit(i)) c[i] += v;
}
int query(int x) {
	int res = 0;
	for (int i = x; i > 0; i -= lowbit(i)) res += c[i];
	return res;
}
void get_fac() {
	fac[1] = 1;
	for (int i = 2; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
}
ll cantor() {
	for (int i = n; i >= 1; i--) cin >> a[i];
	ll res = 0;
	for (int i = 1; i <= n; i++) {
		res += 1ll*query(a[i]) * fac[i-1];
		res %= Mod;
		add(a[i], 1);
	}
	return (res + 1) % Mod;
}

int main() {
	get_fac();
	cin >> n;
	cout << cantor() << endl;
}
/*

ans = sum(a[i] * (i-1)!.....) + 1
a[i] 代表第i个数比i到n的数之中大的个数

*/

//逆康托展开
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
const int Mod = 998244353;
int T, n, order;
ll fac[N];
vector<int> a, ans;
void get_fac() {
	fac[1] = fac[0] = 1;
	for (int i = 2; i <= N; i++) fac[i] = fac[i - 1] * i % Mod;
}
void decantor(int order, int n) {
	for (int i = 1; i <= n; i++) a.push_back(i);

	for (int i = n; i >= 1; i--) {
		int r = order % fac[i - 1];
		int t = order / fac[i - 1];
		order = r;
		ans.push_back(a[t]);
		a.erase(a.begin() + t);
	}
}
int main() {
	get_fac();
	cin >> order >> n;
	order--;
	for (auto x : ans) cout << x << " ";
}

