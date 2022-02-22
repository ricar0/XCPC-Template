template <typename T>
struct Hungary {
	vector<T> vis, match;
	vector<vector<T>> g;
	const int n;
	int ans;
	Hungary(int n): n(n), vis(n), match(n), g(n) {ans = 0;} 

	void init(int n) {
		vis.assign(n, 0);
	}
	void add(int u, int v) {
		g[u].push_back(v);
	}
	bool dfs(int x) {
	    for (auto v : g[x]) {
	        if (!vis[v]) {
	            vis[v] = 1;
	            if (!match[v] || dfs(match[v])) {
	                match[v] = x;
	                return true;
	            }
	        }
	    }
	    return false;
	}
};
