#include <bits/stdc++.h>
using namespace std;
#define INF 1e16
const int N = 1e5 + 200;
const int M = 6 * 1e5 + 300;
int head[M], edge[M], Next[M], ver[M], tot, fa[M], n, m, father[N][32], deep[N];
long long dp[2][N][32], val1, val2, ans_max, ans;

struct node
{
    int x, y, z, vis;
} s[M];

int cmp(node a, node b)
{
    return a.z < b.z;
}

struct Edge {
    void init2() {
        memset(head, 0, sizeof(head));
        tot = 0;
    }
    void add_edge(int a, int b, int c) {
        edge[++tot] = b;
        ver[tot] = c;
        Next[tot] = head[a];
        head[a] = tot;
    }
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    void Kruskal() {
        sort(s + 1, s + 1 + m, cmp);
        for (int i = 1; i <= m; i++)
        {
            int a = find(s[i].x), b = find(s[i].y);
            if (a == b)
                continue;
            s[i].vis = 1;
            fa[a] = b;
            ans += s[i].z;
            add_edge(s[i].x, s[i].y, s[i].z);
            add_edge(s[i].y, s[i].x, s[i].z);
        }
    }
    void bfs(int root) {
        deep[root] = 0;
        queue<int> q;
        q.push(root);
        while (q.size()) {
            int x = q.front(), len = (int)log2(deep[x] + 1);
            q.pop();
            for (int i = head[x]; i; i = Next[i]) {
                int y = edge[i];
                if (y == father[x][0])
                    continue;
                deep[y] = deep[x] + 1;
                father[y][0] = x, dp[0][y][0] = ver[i], dp[1][y][0] = -INF;
                q.push(y);
                for (int t = 1; t <= len; t++) {
                    father[y][t] = father[father[y][t - 1]][t - 1];
                    if (dp[0][y][t - 1] != dp[0][father[y][t - 1]][t - 1]) {
                        dp[0][y][t] = max(dp[0][y][t - 1], dp[0][father[y][t - 1]][t - 1]);
                        dp[1][y][t] = min(dp[0][y][t - 1], dp[0][father[y][t - 1]][t - 1]);
                    }
                    else {
                        dp[0][y][t] = dp[0][y][t - 1];
                        dp[1][y][t] = max(dp[1][y][t - 1], dp[1][father[y][t - 1]][t - 1]);
                    }
                }
                
            }
        }
    }
    inline void update2(int x) {
        if (x > val1)
            val2 = val1, val1 = x;
        else if (x > val2 && x != val1)
            val2 = x;
    }
    inline void update(int x, int t) {
        update2(dp[0][x][t]);
        update2(dp[1][x][t]);
    }
    inline void Lca(int x, int y) {
        val1 = val2 = -INF;
        if (deep[x] < deep[y])
            swap(x, y);
        while (deep[x] > deep[y]) {
            int t = (int)log2(deep[x] - deep[y]);
            update(x, t), x = father[x][t];
        }
        if (x == y)
            return;
        for (int t = (int)log2(deep[x]); t >= 0; t--) {
            if (father[x][t] != father[y][t]) {
                update(x, t), update(y, t);
                x = father[x][t];
                y = father[y][t];
            }
        }
        update(x, 0), update(y, 0);
    }
} g1;

void solve() {
    scanf("%d%d", &n, &m);
    g1.init2();
    for (int i = 1; i <= m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        s[i].x = a, s[i].y = b, s[i].z = c;
        fa[i] = i;
    }
    g1.Kruskal();
    g1.bfs(1);
    ans_max = INF;
    for (int i = 1; i <= m; i++) {
        if (!s[i].vis) {
            g1.Lca(s[i].x, s[i].y);
            if (val1 != s[i].z)
                ans_max = min(ans_max, ans - val1 + s[i].z);
            else
                ans_max = min(ans_max, ans - val2 + s[i].z);
        }
    }
    printf("%lld\n", ans_max);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
#ifdef ACM_LOCAL
	freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	signed test_index_for_debug = 1;
	char acm_local_for_debug = 0;
	do {
		if (acm_local_for_debug == '$') exit(0);
		if (test_index_for_debug > 20)
			throw runtime_error("Check the stdin!!!");
		auto start_clock_for_debug = clock();
		solve();
		auto end_clock_for_debug = clock();
		cout << "Test " << test_index_for_debug << " successful" << endl;
		cerr << "Test " << test_index_for_debug++ << " Run Time: "
			<< double(end_clock_for_debug - start_clock_for_debug) / CLOCKS_PER_SEC << "s" << endl;
		cout << "--------------------------------------------------" << endl;
	} while (cin >> acm_local_for_debug && cin.putback(acm_local_for_debug));
#else
	solve();
#endif
	return 0;
}