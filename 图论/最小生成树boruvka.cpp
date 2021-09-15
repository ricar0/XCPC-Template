ll boruvka() {
	for (int i = 1; i <= n; i++) fa[i] = i;
	ll ans = 0, num = 0;
	while (num < n-1) {
		int tmp = 0;
		for (int i = 1; i <= n; i++) E[i] = PII{INF, INF};
		for (int i = 1; i <= m; i++) {
			int fx = find(e[i].u);
			int fy = find(e[i].v);
			if (fx == fy) continue;
			tmp++;
			E[fx] = min(E[fx], PII{e[i].w, i});
			E[fy] = min(E[fy], PII{e[i].w, i});
		}
		if (tmp == 0) break;
		for (int i = 1; i <= m; i++) {
			int fx = find(e[i].u);
			int fy = find(e[i].v);
			if (fx == fy) continue;
			if (E[fx] == PII{e[i].w, i} || E[fy] == PII{e[i].w, i}) {
				ans += e[i].w;
				num++;
				fa[fx] = fy;
			}
		}
	}
	if (num < n-1) return -1;
	else return ans;
}