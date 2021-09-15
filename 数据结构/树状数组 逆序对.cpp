#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int c[N];
inline int lowbit(int x) {
	return x & -x;
}

void add(int x, int k) {
	for (int i = x; i <= N; i += lowbit(i))
		c[i] += k;
}

int get(int x) {
	int res = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		res += c[i];
	return res;
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		add(x, 1);
		cout << i - get(x) << " ";
	}
}
