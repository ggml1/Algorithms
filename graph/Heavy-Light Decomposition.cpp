const int MAXN = 1e4 + 100;
const int MLOG = log2(MAXN) + 10;

/// HLD
vector<int> chainInd, chainHead;
vector<int> sz;
vector<pii> adj[MAXN];
vector<Edge> edges;
int chainPtr;

// SEGMENT TREE
int n;
vector<int> arr, posArr;
int aptr;
int tree[4 * MAXN];

/// LCA
int par[MLOG][MAXN];
int h[MAXN];

void init() {
  sz = chainInd = vector<int>(n + 1, 0);
  chainHead = vector<int>(n + 1, -1);
  chainPtr = 0;
  for (int i = 0; i < n + 1; ++i) {
    adj[i].clear();
  }
  memset(par, -1, sizeof par);
  /////////////////// END OF HLD STUFF
  edges.clear();
  aptr = 0;
  arr = vector<int>(n + 1, 0);
  posArr = vector<int>(n + 1, 0);
}

void add(int a, int b, int c) {
  adj[a].pb(mp(b, c));
  adj[b].pb(mp(a, c));
}

void update(int pos, int val, int L = 0, int R = aptr - 1, int on = 0) {
  if (L > R || pos < L || pos > R) return;
  if (L == R) {
    tree[on] = val;
  } else {
    int m = (L + R) >> 1;
    update(pos, val, L, m, on + on + 1);
    update(pos, val, m + 1, R, on + on + 2);
    if (tree[on + on + 1] > tree[on + on + 2]) tree[on] = tree[on + on + 1];
    else tree[on] = tree[on + on + 2];
  }
}

void change(int id, int val) {
  Edge x = edges[id];
  int u = x.first.first;
  int v = x.first.second;
  int pos;
  if (par[0][v] == u) pos = posArr[v];
  else pos = posArr[u];
  update(pos, val);
}

int queryS(int qs, int qe, int L = 0, int R = aptr - 1, int on = 0) {
  if (qs > R || qe < L || L > R) return 0;
  if (qs <= L && R <= qe) return tree[on];
  int m = (L + R) >> 1;
  int q1 = queryS(qs, qe, L, m, on + on + 1);
  int q2 = queryS(qs, qe, m + 1, R, on + on + 2);
  return (q1 > q2 ? q1 : q2);
}

int queryH(int u, int v) {
  if (u == v) return 0;
  int uchain, vchain = chainInd[v], ans = 0;
  while (1) {
    uchain = chainInd[u];
    if (uchain == vchain) {
      if (u == v) break;
      int pv = posArr[v] + 1;
      int pu = posArr[u];
      int now = queryS(pv, pu);
      if (now > ans) ans = now;
      break;
    } else {
      int headPos = posArr[chainHead[uchain]];
      int uPos = posArr[u];
      int now = queryS(headPos, uPos);
      if (now > ans) ans = now;
      u = chainHead[uchain];
      u = par[0][u];
    }
  }
  return ans;
}

int lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  int dist = h[u] - h[v];
  for (int i = 0; i < MLOG; ++i) {
    if (dist & (1 << i)) {
      u = par[i][u];
    }
  }
  if (u == v) return u;
  for (int i = MLOG - 1; i >= 0; --i) {
    if (par[i][u] != par[i][v]) {
      u = par[i][u];
      v = par[i][v];
    }
  }
  return par[0][u];
}

void preLCA() {
  for (int i = 1; i < MLOG; ++i) {
    for (int j = 0; j < n; ++j) {
      if (par[i - 1][j] != -1) {
        par[i][j] = par[i - 1][par[i - 1][j]];
      }
    }
  }
}

int query(int u, int v) {
  int anc = lca(u, v);
  int q1 = queryH(u, anc);
  int q2 = queryH(v, anc);
  return (q1 > q2 ? q1 : q2);
}

void build(int L = 0, int R = aptr - 1, int on = 0) {
  if (L == R) {
    tree[on] = arr[L];
  } else {
    int m = (L + R) >> 1;
    build(L, m, on + on + 1);
    build(m + 1, R, on + on + 2);
    if (tree[on + on + 1] > tree[on + on + 2]) tree[on] = tree[on + on + 1];
    else tree[on] = tree[on + on + 2];
  }
}

void dfsp(int v, int p = -1, int dep = 0) {
  sz[v] = 1;
  par[0][v] = p;
  h[v] = dep;
  for (auto edge : adj[v]) {
    if (edge.first == p) continue;
    dfsp(edge.first, v, dep + 1);
    sz[v] += sz[edge.first];
  }
}

void dfsh(int v, int p = -1, int cost = -1) {
  if (chainHead[chainPtr] == -1) chainHead[chainPtr] = v;
  chainInd[v] = chainPtr;
  posArr[v] = aptr;
  arr[aptr++] = cost;
  auto ch = mp(-1, -1);
  for (auto edge : adj[v]) {
    if (edge.first == p) continue;
    if (ch.first == -1 || sz[ch.first] < sz[edge.first]) {
      ch = edge;
    }
  }
  if (ch.first != -1) {
    dfsh(ch.first, v, ch.second);
  }
  for (auto edge : adj[v]) {
    if (edge.first == p || edge == ch) continue;
    ++chainPtr;
    dfsh(edge.first, v, edge.second);
  }
}