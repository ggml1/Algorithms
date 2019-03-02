struct Edge {
  int from, to;
  ll cost;
  Edge(int _from = 0, int _to = 0, ll _cost = 0) :
    from(_from), to(_to), cost(_cost) {}
  bool operator != (const Edge& b) const {
    int u = min(from, to), v = max(from, to);
    int bu = min(b.from, b.to), bv = max(b.from, b.to);
    return u != bu || v != bv || cost != b.cost;
  }
  bool operator < (const Edge& b) const {
    // modify accordingly
    return cost < b.cost;
  }
};

void init() {
  sz = vector<int>(n + 1, 0);
  idx = vector<int>(n + 1, 0);
  head = vector<int>(n + 1, -1);
  cptr = 0;
  for (int i = 0; i < n + 1; ++i) {
    adj[i].clear();
  }
  memset(par, 0, sizeof par);
  /////////////////// END OF HLD STUFF
  aptr = 0;
  pos = vector<int>(n + 1, 0);
}

void add(int a, int b, ll c = 0) {
  adj[a].emplace_back(a, b, c);
  adj[b].emplace_back(b, a, c);
}

void queryH(int u, int v) {
  while (idx[u] != idx[v]) {
    int a = pos[head[idx[u]]];
    int b = pos[u];
    query(a, b);
    u = par[0][head[idx[u]]];
  }
  if (u == v) return;
  int a = pos[v] + 1, b = pos[u];
  query(a, b);
}

int lca(int u, int v) {
  if (h[u] > h[v]) swap(u, v);
  int d = h[v] - h[u];
  for (int i = 0; i < MLOG; ++i) {
    if (d & (1 << i)) v = par[i][v];
  }
  if (u == v) return u;
  for (int i = MLOG - 1; i >= 0; --i) {
    if (par[i][u] != par[i][v]) {
      u = par[i][u];
      v = par[i][v]
    }
  }
  return par[0][u];
}

void query(int u, int v) {
  int anc = lca(u, v);
  queryH(u, anc);
  queryH(v, anc);
}

void dfsp(int v, int dep = 0) {
  sz[v] = 1; h[v] = dep;
  for (int i = 1; i < MLOG; ++i) {
    par[i][v] = par[i - 1][par[i - 1][v]];
  }
  Edge &grt = adj[v][0];
  for (Edge &nxt : adj[v]) {
    if (nxt.to == par[0][v]) continue;
    par[0][nxt.to] = v;
    dfsp(nxt.to, dep + 1);
    sz[v] += sz[nxt.to];
    if (grt.to == par[0][v] || sz[nxt.to] > sz[grt.to]) swap(grt, nxt);
  }
}

void dfsh(int v, ll cost = -1) {
  if (head[cptr] == -1) head[cptr] = v;
  idx[v] = cptr;
  pos[v] = aptr++;
  // arr[aptr++] = cost;
  for (Edge nxt : adj[v]) {
    if (nxt.to == par[0][v]) continue;
    cptr += (nxt != adj[v][0]);
    dfsh(nxt.to, nxt.cost);
  }
}