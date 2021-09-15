const int N = 200 + 5;
int G[N][N];
int ans[N];
int vis[N];
int res, n;
void dfs(int x, int cnt) {
    if (x > n) {
        if (cnt > res) {
            res = cnt;
            for (int i = 1; i <= n; i++)
                ans[i] = vis[i];
        }
        return;
    }
    if (cnt + n - x + 1 < res) return;
    int pd = 0;
    for (int i = 1; i < x; i++)
        if (vis[i] && G[i][x]) {
            pd = 1;
            break;
        }
    if (!pd) {
        vis[x] = 1;
        dfs(x+1, cnt+1);
        vis[x] = 0;
    }
    dfs(x+1, cnt);
}
