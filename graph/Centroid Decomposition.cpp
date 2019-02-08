vector<set<int>> adj;

struct CentroidDecomposition {
	vector<set<int>> tree;
	vector<int> par, st, ans, h;
	vector<vector<int>> dp;
	int ML;

	CentroidDecomposition(vector<set<int>> &t) : tree(t) {
		int n = tree.size();
		par.resize(n);
		st.resize(n);
		h = vector<int>(n, -1);
		ans = vector<int>(n, 123456789);
		dp.resize(n);

		ML = log2(n);

		for (int i = 0; i < n; ++i) {
			dp[i].resize(ML);
		}

		bfs(1);
		pre(1, -1);
		decompose(1, -1);
	}

	void pre(int v, int p) {
		dp[v][0] = p;

		if (p + 1) {
			h[v] = h[p] + 1;
		}

		for (int i = 1; i < ML; ++i) {
			if (dp[v][i - 1] + 1) {
				dp[v][i] = dp[dp[v][i - 1]][i - 1];
			}
		}

		for (auto u : tree[v]) {
			if (p - u) {
				pre(u, v);
			}
		}
	}

	int lca(int v, int u) {
		if (h[v] < h[u]) swap(v, u);

		for (int i = ML - 1; i >= 0; --i) {
			if (dp[v][i] + 1 && h[dp[v][i]] >= h[u]) {
				v = dp[v][i];
			}
		}

		if (v == u) return v;

		for (int i = ML - 1; i >= 0; --i) {
			if (dp[v][i] - dp[u][i]) {
				v = dp[v][i];
				u = dp[u][i];
			}
		}

		return dp[v][0];
	}

	void bfs(int f) {
		queue<int> q;
		q.push(f);
		h[f] = 0;

		while (!q.empty()) {
			int u = q.front();
			q.pop();

			for (int v : tree[u]) {
				if (h[v] == -1) {
					h[v] = h[u] + 1;
					q.push(v);
				}
			}
		}
	}

	int subTreeSz(int u, int p) {
		st[u] = 1;

		for (auto v : tree[u]) {
			if (v != p) st[u] += subTreeSz(v, u);
		}

		return st[u];
	}

	int getCentroid(int u, int p, int sz) {
		for (auto v : tree[u]) {
			if (v != p && st[v] > sz / 2) return getCentroid(v, u, sz);
		}

		return u;
	}

	void decompose(int u, int p) {
		int sz = subTreeSz(u, p);
		int centroid = getCentroid(u, u, sz);
		if (p == -1) p = centroid;
		par[centroid] = p;

		for (auto v : tree[centroid]) {
			tree[v].erase(centroid);
			decompose(v, centroid);
		}

		tree[centroid].clear();
	}

	int dist(int x, int y) {
		return h[x] + h[y] - 2 * h[lca(x, y)];
	}

	int query(int v) {
		int x = v;
		int ret = INT_MAX;
		while (1) {
			// cout << v << ' ' << x << ' ' << ans[v] << ' ' << dist(x, v) << endl;
			ret = min(ret, ans[v] + dist(x, v));
			if (v == par[v]) break;
			v = par[v];
		}
		return ret;
	}

	void upd(int v) {
		int x = v;
		while (1) {
			ans[v] = min(ans[v], dist(x, v));
			if (v == par[v]) break;
			v = par[v];
		}
	}
};

void add(int a, int b) {
	adj[a].insert(b);
	adj[b].insert(a);
}