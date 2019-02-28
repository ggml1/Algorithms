void init() {
  sz = vector<int>(n + 1, 0);
  idx = vector<int>(n + 1, 0);
  head = vector<int>(n + 1, -1);
  cptr = 0;
  for (int i = 0; i < n + 1; ++i) {
    adj[i].clear();
  }
  memset(par, -1, sizeof par);
  /////////////////// END OF HLD STUFF
  aptr = 0;
  pos = vector<int>(n + 1, 0);
}

void add(int a, int b) {
  adj[a].push_back(b);
  adj[b].push_back(a);
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

void query(int u, int v) {
  int anc = lca(u, v);
  queryH(u, anc);
  queryH(v, anc);
}

void dfsp(int v, int p = -1, int dep = 0) {
  sz[v] = 1;
  par[0][v] = p;
  h[v] = dep;
  for (int i = 0; i < adj[v].size(); ++i) {
    if (adj[v][i] == p) continue;
    dfsp(adj[v][i], v, dep + 1);
    sz[v] += sz[adj[v][i]];
    if (adj[v][0] == p || sz[adj[v][i]] > sz[adj[v][0]]) swap(adj[v][0], adj[v][i]);
  }
}

void dfsh(int v, int p = -1) {
  if (head[cptr] == -1) head[cptr] = v;
  idx[v] = cptr;
  pos[v] = aptr++;
  for (int i = 0; i < adj[v].size(); ++i) {
    if (adj[v][i] == p) continue;
    cptr += (i > 0);
    dfsh(adj[v][i], v);
  }
}