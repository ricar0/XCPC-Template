int prim() {
	memset(vis, 0, sizeof vis);
	memset(dis, 0x3f, sizeof dis);
	int ans = 0;
	for (int i = h[1]; ~i; i = e[i].next) {
		dis[e[i].to] = min(dis[e[i].to], e[i].vi);
	}
	dis[1] = 0, vis[1] = 1;
	for (int i = 2; i <= n; i++) {
		int minn = INF;
		int k;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && dis[j] < minn) {
				minn = dis[j];
				k = j;
			}
		}
		if (minn == INF) return -1;
		ans += minn;
		vis[k] = 1;
		for (int j = h[k]; ~j; j = e[j].next) {
			dis[e[j].to] = min(dis[e[j].to], e[j].vi);
		}
	}
	return ans;
}