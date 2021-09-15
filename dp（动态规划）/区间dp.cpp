#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define ACM_LOCAL

const int N = 200 + 5;
const int Mod = 1e9 + 7;
int n, s[N], f1[N][N], f2[N][N];

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> s[i], s[i+n] = s[i];
    for (int i = 1; i <= 2*n; i++) s[i] += s[i-1];

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i + len - 1 <= 2*n; i++) {
            int j = i + len - 1;
            f1[i][j] = 1e8;
            for (int k = i; k < j; k++) {
                f1[i][j] = min(f1[i][j], f1[i][k] + f1[k+1][j] + s[j] - s[i-1]);
                f2[i][j] = max(f2[i][j], f2[i][k] + f2[k+1][j] + s[j] - s[i-1]);
            }
        }
    }
    int Max = 0, Min = 1e8;
    for (int i = 1; i + n - 1 <= 2*n; i++) {
        Max = max(Max, f2[i][i+n-1]);
        Min = min(Min, f1[i][i+n-1]);
    }
    cout << Min << endl;
    cout << Max << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
    return 0;
}
