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
typedef pair<int, int> PII;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const int N = 310;
int n, m, match[N], pre[N];
bool vis[N];
ll g[N][N];
ll val1[N], val2[N], slack[N];

void bfs(int p){
    memset(pre, 0, sizeof pre);
    memset(slack, 0x3f, sizeof slack);
    match[0] = p;
    int x = 0, nex = 0;
    do{
        vis[x] = true;
        int y = match[x];
        ll d = INF;
        for (int i = 1; i <= m; i++)
            if (!vis[i]){
                if (slack[i] > val1[y] + val2[i] - g[y][i])
                    slack[i] = val1[y] + val2[i] - g[y][i], pre[i] = x;
                if (slack[i] < d)
                    d = slack[i], nex = i;
            }
        for (int i = 0; i <= m; i++){
            if (vis[i])
                val1[match[i]] -= d, val2[i] += d;
            else
                slack[i] -= d;
        }
        x = nex;
    } while (match[x]);
    while (x){
        match[x] = match[pre[x]];
        x = pre[x];
    }
}

ll KM(){
    memset(match, 0, sizeof match);
    memset(val1, 0, sizeof val1);
    memset(val2, 0, sizeof val2);
    for (int i = 1; i <= n; i++){
        memset(vis, false, sizeof vis);
        bfs(i);
    }
    ll res = 0;
    for (int i = 1; i <= m; i++) res += g[match[i]][i];
    return res;
}
