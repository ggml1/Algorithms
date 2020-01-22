template <typename T>
struct Flow {
	struct Edge {
		int to;
		T cap;
		Edge() {}
		Edge(int a, T b) : to(a), cap(b) {}
	};

	int n;
	vector<vector<int>> adj;
	vector<Edge> edges;
	vector<int> level, on;
	vector<bool> visited;
	
	Flow(int a = 0) {
		n = a;
		adj.resize(a + 2);
		visited = vector<bool>(a + 2, 0);
	}

	void init(int a) {
		adj.clear();
		edges.clear();
		adj.resize(a + 2);
		visited = vector<bool>(a + 2, 0);
		n = a;
	}

	void addEdge(int from, int to, T cap) {
		adj[from].push_back(int(edges.size()));
		edges.push_back(Edge(to, cap));
		adj[to].push_back(int(edges.size()));
		edges.push_back(Edge(from, 0));
	}

	bool bfs(int src, int sink) {
		level = vector<int>(n + 2, 0);
		queue<int> q;
		level[src] = 0;
		q.push(src);
		while(!q.empty()) {
			int cur = q.front();
			q.pop();
			for(int id : adj[cur]) {
				if (edges[id].cap == 0) continue;
				int to = edges[id].to;
				if (level[to] == 0 && to != src) {
					q.push(to);
					level[to] = level[cur] + 1;
				}
			}
		}
		return level[sink] > 0;
	}

	T dfs(int v, int sink, T cur) {
		if (v == sink) return cur;
		for(; on[v] < (int) adj[v].size(); on[v]++) {
			int id = adj[v][on[v]];
			if (level[v] + 1 != level[edges[id].to]) {
				continue;
			}
			if (edges[id].cap) {
				T temp = dfs(edges[id].to, sink, min(cur, edges[id].cap));
				if (temp) {
					edges[id].cap -= temp;
					edges[id ^ 1].cap += temp;
					return temp;
				}
			}
		}
		return 0;
	}

	T mf(int src, int sink) {
		T ans = 0;
		while (bfs(src, sink)) {
			on = vector<int>(n + 2, 0);
			T cur;
			while ((cur = dfs(src, sink, 1e9))) {
				ans += cur;
			}
		}
		return ans;
	}

	void travel(int s) {
		visited[s] = 1;
		for (int eid : adj[s]) {
			if (eid & 1) continue;
			Edge cur = edges[eid];
			int nxt = cur.to;
			if (!cur.cap && !visited[nxt]) travel(nxt);
		}
	}
};
