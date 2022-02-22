template <typename T>
struct Maxflow {
	vector<int> h, deep, cur, vis;
    int cnt, st, ed, n, m;
    T maxflow;
    struct Edge {
        int to, next;
        T cap;
    };
    vector<Edge> e;
    Maxflow(int n, int m): n(n), m(m),e(m<<1),h(n, -1),deep(n),cur(n),vis(n),cnt(0),st(0),ed(0){}
    void add(int u, int v, T cap) {
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
    	deep.assign(n, -1);
    	h=cur;
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

    T dfs(int u, T mx) {
        T a;
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
        T res;
        while (bfs()) {
            while (1) {
                res = dfs(st, inf);
                if (!res) break;
                maxflow += res;
            }
        }
    }
    void construct(int x) {
    	queue<int> q;
    	q.push(x);
    	while (q.size()) {
    		int now = q.front();
    		q.pop();
    		vis[now] = 1;
    		for (int i = h[now]; ~i; i = e[i].next) {
    			int v = e[i].to;
    			if (!vis[v] && e[i].cap) q.push(v);
    		}
    	}
    }
};
