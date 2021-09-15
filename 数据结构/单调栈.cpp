#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 10;
int a[N], n, idx[N];
stack<int> stk;
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) {
        while (stk.size() && a[stk.top()] < a[i]) {
            idx[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }
    for (int i = 1; i <= n; i++) cout << idx[i] << " ";
}