typedef long long ll;
typedef pair<int, int> PII;
const int N = 1e3 + 10, M = 2e5 + 10, INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
int state[N][11], n, p, cap[N], st, ed;
struct Maxflow {
    int h[N], cnt, maxflow, deep[N], cur[N];
    struct Edge {
        int to, next;
        ll cap;
    } e[M<<1];

    void init() {
        memset(h, -1, sizeof h);
        cnt = maxflow = 0;
    }
    void add(int u, int v, int cap) {
        e[cnt].to = v;
        e[cnt].cap = cap;
        e[cnt].next = h[u];
        h[u] = cnt++;

        e[cnt].to = u;
        e[cnt].cap = 0;
        e[cnt].next = h[v];
        h[v] = cnt++;

    }

    bool bfs() {
        for (int i = 0; i <= ed; i++) deep[i] = -1, cur[i] = h[i];
        queue<int> q; q.push(st); deep[st] = 0;
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i = h[u]; ~i; i = e[i].next) {
                int v = e[i].to;
                if (e[i].cap && deep[v] == -1) {
                    deep[v] = deep[u] + 1;
                    q.push(v);
                }
            }
        }
        if (deep[ed] >= 0) return true;
        else return false;
    }

    ll dfs(int u, ll mx) {
        ll a;
        if (u == ed) return mx;
        for (int i = cur[u]; ~i; i = e[i].next) {
            cur[u] = i;//优化
            int v = e[i].to;
            if (e[i].cap && deep[v] == deep[u] + 1 && (a = dfs(v, min(e[i].cap, mx)))) {
                e[i].cap -= a;
                e[i ^ 1].cap += a;
                return a;
            }
        }
        return 0;
    }

    void dinic() {
        ll res;
        while (bfs()) {
            while (1) {
                res = dfs(st, INF);
                if (!res) break;
                maxflow += res;
            }
        }
    }
}mf;
