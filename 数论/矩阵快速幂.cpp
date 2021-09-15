#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ACM_LOCAL
inline ll read(){
   ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int N = 100 + 5;
const int MOD = 1e9 + 7;

ll n, k;
struct Matrix {
	ll a[N][N];
	inline Matrix operator * (const Matrix& rhs) {
		Matrix ret;
		memset(&ret, 0, sizeof ret);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					ret.a[i][j] = (ret.a[i][j] + a[i][k] * rhs.a[k][j] % MOD) % MOD;
		return ret;
	}
}mp;

Matrix ksm(Matrix &a, ll k) {
    Matrix ans;
    memset(&ans, 0, sizeof ans);
    for (int i = 1; i <= n; i++) ans.a[i][i] = 1;
    while (k) {
        if (k & 1) ans = ans * a;
        a = a * a;
        k >>= 1;
    }
    return ans;
}

void solve() {
    n = read(), k = read();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            mp.a[i][j] = read();

    Matrix b = ksm(mp, k);
    for (int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++) printf("%lld ", b.a[i][j]);
        puts("");
    }
}

signed main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);
    //cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve();
    return 0;
}