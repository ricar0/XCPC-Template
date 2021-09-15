#include <bits/stdc++.h>
#define ACM_LOCAL
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const int MOD = 1e9 + 7;
int sz[N], son[N], h[N], tot, col[N], cnt[N], vis[N], mx;
ll sum, ans[N];
struct Edge {
    int to, next;
}e[M];

void add(int u, int v) {
    e[tot].to = v;
    e[tot].next = h[u];
    h[u] = tot++;
}

void dfs(int u, int fa) {
    sz[u] = 1;
    for (int i = h[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (!son[u] || sz[v] > sz[son[u]])
            son[u] = v;
    }
}

void count(int u, int fa, int k) {
    //统计子树信息
    
    
    //
    for (int i = h[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa || vis[v]) continue;
        count(v, u, k);
    }
}

void dsu(int u, int fa, int keep) {
    for (int i = h[u]; ~i; i = e[i].next) {
        int v = e[i].to;
        if (v == fa || son[u] == v) continue;
        dsu(v, u, 0);//查询轻儿子
    }
    if (son[u]) dsu(son[u], u, 1), vis[son[u]] = 1;//查询重儿子
    count(u, fa, 1);//统计子树信息
    //统计答案
    if (son[u]) vis[son[u]] = 0;
    if (!keep) count(u, fa, -1), mx = sum = 0;//撤回信息
}
